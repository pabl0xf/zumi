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
        command = input("what?")            
        cnt = int(input("how much?"))

        if command == 'w':
            command = 'up' 
        elif command == 'a':
            command = 'left'
        elif command == 's':
            command = 'right' 
        elif command == 'e':
            command = 'eiffel'
        elif command == 'c':
            command = 'chicago'
        elif command == 't':
            command = 'seattle'
        elif command == 'n':
            command = 'nyc'
        elif command == 'z':
            command = 'china'
        elif command == 'b':
            command = 'bigben'
        elif command == 'k':
            command = 'khalifa'
        elif command == 'x':
            command = "start"
        elif command == 'i':
            command = "intersection"
        else:
            print("# bad command: " + command)
            cnt = 0

        print(command + "!")
        time.sleep(1)
        
        while cnt != 0:
            print(cnt)
            cnt = cnt - 1
            image = camera.run()
            image = cv2.flip(image, -1)

            time.sleep(0.5)
            
            if command in ['up', 'left', 'right', 'eiffel', 'start', 'chicago', 'nyc', 'china', 'bigben', 'khalifa', 'seattle', 'intersection']:
                file_name = "/home/pi/zumi/sample/deep-learning-demos/tourist/images/" + which_robot + "." + str(time.time()) + "." + command + ".jpg"
                image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
                cv2.imwrite(file_name, image)

finally:
    clean_up()
