import sys
sys.path.insert(0,'/home/pi/zumi/lib')
import Engine as engine
from TawnCam import PiCamera
import time
import cv2
from IPython import display
import PIL.Image
import TouristDemoHelper as tourist_demo

def clean_up():
    camera.shutdown() 
    engine.stop()
    exit()

camera = PiCamera(image_w=64, image_h=64, image_d=3, framerate=10)
command = ""
  
which_robot = tourist_demo.get_robot_name()
print("ready to train with " + which_robot + "!")

tourist_demo.calibrate_motors()

try:
    while True:        
        
        image = camera.run()
        image = cv2.flip(image, -1)

        command = input("")            

        if command == 'w':
            command = 'up' 
        elif command == 'a':
            command = 'left'
        elif command == 's':
            command = 'right' 
        elif command == 'e':
            command = 'eiffel'
            print(command + "!")
        elif command == 'c':
            command = 'chicago'
            print(command + "!")
        elif command == 't':
            command = 'seattle'
            print(command + "!")
        elif command == 'n':
            command = 'nyc'
            print(command + "!")
        elif command == 'z':
            command = 'china'
            print(command + "!")
        elif command == 'b':
            command = 'bigben'
            print(command + "!")
        elif command == 'k':
            command = 'khalifa'
            print(command + "!")
        elif command == 'x':
            command = "start"
            print(command + "!")
        elif command == 'i':
            command = "intersection"
            print(command + "!")     

        tourist_demo.drive_and_stop(command)

        if command in tourist_demo.landmarks.values():
            file_name = "/home/pi/zumi/sample/deep-learning-demos/tourist/images/" + which_robot + "." + str(time.time()) + "." + command + ".jpg"
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            cv2.imwrite(file_name, image)
        else:
            print("# bad command: " + command)
        
finally:
    print("Error")
    clean_up()
