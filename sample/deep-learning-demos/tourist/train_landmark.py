import sys
sys.path.insert(0,'/home/pi/zumi/lib')
import EngineV3 as engine
import picamera
import time
import cv2
from IPython import display
import PIL.Image

def clean_up():
    camera.close()
    engine.stop()
    exit()

from picamera import PiCamera
camera = PiCamera()
resolution = 64
camera.resolution = (resolution, resolution)
camera.start_preview()
engine.set_speed(20)

command = ""

try:
    while True:        
        
        camera.capture("temp.jpg")
        image = cv2.imread("temp.jpg")
        image = cv2.flip(image, -1)

        command = input("which direction?")           

        if command == 'w':
            command = 'up' 
            engine.forward_a_bit()
        elif command == 'a':
            command = 'left'
            engine.left_a_bit() 
        elif command == 's':
            command = 'right' 
            engine.right_a_bit()
        elif command == 'z':
            command = 'eiffel' 
           
        engine.stop()
        
        file_name = "/home/pi/zumi/sample/deep-learning-demos/tourist/images/" + str(time.time()) + "." + command + ".jpg"
        cv2.imwrite(file_name, image)
        
finally:
    clean_up()
