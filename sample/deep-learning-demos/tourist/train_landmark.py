import sys
sys.path.insert(0,'/home/pi/zumi/lib')
import Engine as engine
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

engine.set_speed(50)

command = ""

try:
    while True:        
        
        image = camera.run()
        image = cv2.flip(image, -1)

        command = input("")            

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
            print(command + "!")
        elif command == 'c':
            command = 'chicago'
            print(command + "!")
        elif command == 'x':
            command = "start"
            print(command + "!")
         
        engine.stop()
        
        if command in ['up', 'left', 'right', 'eiffel', 'start', 'chicago']:
            file_name = "/home/pi/zumi/sample/deep-learning-demos/tourist/images/" + str(time.time()) + "." + command + ".jpg"
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            cv2.imwrite(file_name, image)
        else:
            print("# bad command: " + command)
        
finally:
    clean_up()
