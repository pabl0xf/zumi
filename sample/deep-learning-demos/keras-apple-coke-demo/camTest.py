print("Importing picamera...")
import picamera
import picamera.array
import picamera, cv2
from IPython import display

import sys
sys.path.insert(0, '/home/pi/zumi/lib')
print("Importing Engine...")
import Engine as engine

print("Importing Speaker...")
print("Importing picamera...")
import picamera
import picamera.array
import picamera, cv2
from IPython import display

import sys
sys.path.insert(0, '/home/pi/zumi/lib')
print("Importing Engine...")
import Engine as engine

print("Importing Speaker...")
import Speaker as speaker

print("Importing numpy...")
import numpy as np

print("Importing PIL...")
from PIL import Image

# print("Importing keras...")
# from keras.models import load_model
# from keras.preprocessing.image import img_to_array

# print("Loading model...")
# model = load_model('third_try.h5')

print("\nFinished imports")

def coke():
        print("\n\n🍹 🍹 🍹 🍹 🍹 Coke! 🍹 🍹 🍹 🍹 🍹\n\n")
        engine.go_backward()
        time.sleep(2)
        engine.stop()
        speaker.play_sad_sound()

def apple():
    print("\n\n🍏 🍏 🍏 🍏 🍏 Apple! 🍏 🍏 🍏 🍏 🍏\n\n")
    engine.turn_right()
    time.sleep(3)
    engine.stop()
    speaker.play_happy_sound()
def nothing():
    print("\n\n\tNo object detected!\n\n")

functionsKey = {
        "1": nothing,
        "0": apple,
        "2": coke
        } 

# WINDOW_NAME = 'stream'
# cv2.namedWindow(WINDOW_NAME)
# cv2.startWindowThread()

try:
    while True:
        with picamera.PiCamera() as camera:                          
            camera.resolution = (220, 180)
            camera.capture("tmp.jpg")
            img = cv2.imread("tmp.jpg")
            # pred = model.predict(img[None, :, :, :])
            # res = np.argmax(pred[0])
            # functionsKey[(str(int(res)))] ()
            cv2.imshow("hello", img)
            # display.clear_output(wait=True)
            # display.display(display.Image("tmp.jpg"))                                                                                                                                   
            if cv2.waitKey(1) & 0xFF == ord('p'):
                 print("hello")                                                                                                                                                                                                                                                                                                                                                 
except KeyboardInterrupt: 
    print("\n\nExiting...\n")
