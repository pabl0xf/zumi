print("Importing opencv and numpy...")
import cv2
import numpy as np
import picamera
from picamera.array import PiRGBArray
import io
import time

print("Importing Keras...")
from keras.models import load_model
from keras.preprocessing.image import img_to_array

print("Loading model...")
model = load_model('manbag1.h5')
print("Model imported")

#For USB WebCam
#cap = cv2.VideoCapture(0)
#ret, frame = cap.read()
#height, width, channels = frame.shape
#nH = 150/height
#nW = 150/width
##

output = ["Lego Man", "Plastic Bag"]
with picamera.PiCamera() as camera:
    camera.resolution = (150, 150)
    rawCapture = PiRGBArray(camera)
    
    for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
        image = frame.array  #grab the raw NumPy array representing the image
        rawCapture.truncate(0) # clear the stream in preparation for the next frame
        # This image can now be used with openCV...
        image = cv2.flip(image, 0)
        time.sleep(1)
        x = np.expand_dims(image, axis=0)
        pred = model.predict_classes(x)
        print(output[pred[0]])

#with picamera.PiCamera() as camera:
#    try:
#        camera.start_preview()
#        camera.resolution = (150, 150)
#        while 1:
#            camera.capture(rawCapture,format='bgr')
#            frame = rawCapture.array
#            x = np.expand_dims(frame, axis=0)
#            pred = model.predict_classes(x)
#            print(output[pred[0]])
#            #cv2.imshow(str(frame.shape), frame)
#            rawCapture.truncate(0)
#            if cv2.waitKey(1) & 0xFf == ord('q'):
#                break
#    except KeyboardInterrupt:
#        camera.stop_preview()
