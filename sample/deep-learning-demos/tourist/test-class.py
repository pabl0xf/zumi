# Python 3 code that compiles a neural model then prints the predictions
# in realtime

# import modules
from picamera.array import PiRGBArray
from picamera import PiCamera
import sys
import numpy as np
from PIL import Image
from keras.models import Sequential
from keras.layers import Conv2D, MaxPooling2D, Activation, Flatten, Dense, Dropout, LeakyReLU
from keras.preprocessing.image import img_to_array
from keras import backend as K
import time

# if input images need to be normalized, pass them through this function
def normalize(image):
	maximum = image.max()
	if maximum > 0:
		scaledValue = 255.0/maximum
	else:
		scaledValue = 1.0
	normalizedImage = image*scaledValue
	return normalizedImage

# set input resolution
WIDTH = 64
HEIGHT = 64

if K.image_data_format() == 'channels_first':
	input_shape = (3, WIDTH, HEIGHT)
else:
	input_shape = (WIDTH, HEIGHT, 3)

#######################
# recreate model here #
#######################

model = Sequential()

model.add(Conv2D(32, kernel_size=(3,3),
                 activation='relu',
                 input_shape=(64,64,3)))
model.add(Conv2D(64, (3, 3), activation='relu'))
model.add(MaxPooling2D(pool_size=(2, 2)))
model.add(Conv2D(64, (3, 3), activation='relu'))
model.add(MaxPooling2D(pool_size=(2, 2)))
model.add(Flatten())
model.add(Dense(128, activation='relu'))
model.add(Dense(7, activation='softmax'))

# load weights
model.load_weights('weights-whoseop6.hdf5')

# compile
model.compile(loss='categorical_crossentropy',
	optimizer='adam',
	metrics=['accuracy'])

########################

# set up camera
camera = PiCamera()
camera.resolution = (WIDTH, HEIGHT)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(WIDTH, HEIGHT))

# let camera warm up
time.sleep(0.1)

try:
        # take video stream
	for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
                # take frame
		x = Image.fromarray(frame.array)
		# flip upside down
		x = x.transpose(Image.ROTATE_180)
		# normalize image
		#x = normalize(x)
		# create a 3rd dimension
		x = np.expand_dims(x, axis=0)
		
		# make a prediction and print
		# pred returns an array of percentages, read in alphebetical
		# order, from left to right
                # preds returns the number of the predicted class
		pred = model.predict(x)
		preds = model.predict_classes(x)
		print(pred, preds)

		# clear camera buffer
		rawCapture.truncate(0)
except KeyboardInterrupt:
		print("\nExiting...")
