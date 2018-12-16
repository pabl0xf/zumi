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
    
if len(sys.argv) == 1:
    print("Please use an argument with the robot name. e.g. python3 train_landmark.py jumi")
    exit()  

camera = PiCamera(image_w=64, image_h=64, image_d=3, framerate=10)

engine.set_speed(50)

command = ""

    
which_robot = sys.argv[1] 
print("ready to train with " + which_robot + "!")

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
        elif command == 'e':
            command = 'eiffel'
            engine.forward_a_bit()
            print(command + "!")
        elif command == 'c':
            command = 'chicago'
            engine.forward_a_bit()
            print(command + "!")
        elif command == 't':
            command = 'seattle'
            engine.forward_a_bit()
            print(command + "!")
        elif command == 'n':
            command = 'nyc'
            engine.forward_a_bit()
            print(command + "!")
        elif command == 'z':
            command = 'china'
            engine.forward_a_bit()
            print(command + "!")
        elif command == 'b':
            command = 'bigben'
            engine.forward_a_bit()
            print(command + "!")
        elif command == 'k':
            command = 'khalifa'
            engine.forward_a_bit()
            print(command + "!")
        elif command == 'x':
            command = "start"
            engine.forward_a_bit()
            print(command + "!")
        elif command == 'i':
            command = "intersection"
            engine.forward_a_bit()
            print(command + "!")     
        
        engine.stop()
        
        if command in ['up', 'left', 'right', 'eiffel', 'start', 'chicago', 'nyc', 'china', 'bigben', 'khalifa', 'seattle']:
            file_name = "/home/pi/zumi/sample/deep-learning-demos/tourist/images/" + which_robot + "." + str(time.time()) + "." + command + ".jpg"
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            cv2.imwrite(file_name, image)
        else:
            print("# bad command: " + command)
        
finally:
    clean_up()
