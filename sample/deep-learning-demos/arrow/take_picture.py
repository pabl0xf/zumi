import sys
sys.path.insert(0,'/home/pi/zumi/lib')
import EngineV3 as engine
from TawnCam import PiCamera
import time
import cv2
from IPython import display
import PIL.Image

def clean_up():
    camera.shutdown() 
    engine.stop()
    exit()

camera = PiCamera(image_w=64, image_h=64, image_d=3, framerate=10)

command = ""

try:
    while True:        
        
        image = camera.run()
        image = cv2.flip(image, -1)

        command = input("")            

        if command == 'a':
            command = 'left' 
        elif command == 's':
            command = 'stop'
        elif command == 'd':
            command = 'right' 

        print(command + "!")
         
        
        if command in ['up', 'left', 'right', 'eiffel', 'start', 'chicago']:
            file_name = "/home/pi/zumi/sample/deep-learning-demos/arrow/images/" + str(time.time()) + "." + command + ".jpg"
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            cv2.imwrite(file_name, image)
        else:
            print("# bad command: " + command)
        
finally:
    clean_up()
