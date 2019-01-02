from picamera.array import PiRGBArray
from picamera import PiCamera
import sys
import numpy as np
from keras.models import Sequential
from keras.layers import Activation, Flatten, Dense, Conv2D, MaxPooling2D
from keras.preprocessing.image import array_to_img
from keras import backend as K
import time
import TouristDemoHelper as tourist_demo
drive_model = tourist_demo.load_model("landmark")

WIDTH = 64
HEIGHT = 64

if K.image_data_format() == 'channels_first':
	input_shape = (3, WIDTH, HEIGHT)
else:
	input_shape = (WIDTH, HEIGHT, 3)

model = Sequential()

model.add(Conv2D(32, (3, 3), input_shape=input_shape))
model.add(Activation('relu'))
model.add(MaxPooling2D(pool_size=(2, 2)))

model.add(Conv2D(32, (3, 3)))
model.add(Activation('relu'))
model.add(MaxPooling2D(pool_size=(2, 2)))

model.add(Flatten())

model.add(Dense(128))
model.add(Activation('relu'))
model.add(Dense(2))
model.add(Activation('sigmoid'))
model.load_weights('/home/pi/zumi/sample/deep-learning-demos/tourist/drawing_weights.hdf5')

model.compile(loss='categorical_crossentropy',
	optimizer='adam',
	metrics=['accuracy'])

while True :
    try :
        camera = PiCamera()
        camera.resolution = (WIDTH, HEIGHT)
        camera.hflip = True
        camera.vflip = True
        camera.framerate = 32
        rawCapture = PiRGBArray(camera, size=(WIDTH, HEIGHT))

        time.sleep(0.1)

        null = input("Press enter to begin!")

        for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
            x = frame.array
            maximum = x.max()
            scaledValue = 1.0
            if maximum > 0:
                scaledValue = 255.0/maximum
            y = scaledValue * x
            y = np.expand_dims(y, axis=0)
            pred = model.predict(y)
            preds = model.predict_classes(y)

            rawCapture.truncate(0)

            #Decide whether 'nyc' or 'china' based on pred

            if int(preds) == 0:
                print("China")
                camera.close()
                tourist_demo.drive_to_landmark("china", drive_model)
                break
            else:
                print("NYC")
                camera.close()
                tourist_demo.drive_to_landmark("nyc", drive_model)
                break
    except:
        print("hi")