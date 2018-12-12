import sys
sys.path.insert(0,'/home/pi/zumi/lib')
from TawnCam import PiCamera
import time
import cv2
from IPython import display
import PIL.Image


def clean_up():
    camera.shutdown() 
    exit()

camera = PiCamera(image_w=64, image_h=64, image_d=3, framerate=10)

command = 'start'
STATE = ''
cnt = 0
end_cnt = 100
try:
    while True:        
        if end_cnt == cnt :
            cmmand = 'start'
        image = camera.run()
        image = cv2.flip(image, -1)
        
        if command == 'start':
            command = input("start:")            
            end_cnt = input("how much:")
            cnt = 0
            if command == 'a':
                STATE = 'ar_left' 
            elif command == 's':
                STATE = 'ar_stop'
            elif command == 'd':
                STATE = 'ar_right' 
            command = "" 
        cnt += 1
        print(STATE + "!" + cnt)
        
        
        #if command !="":
        #    print ("restart")
        #    STATE = "re_start"
        if command == "" and STATE in ['ar_stop', 'ar_left', 'ar_right']:
            file_name = "/home/pi/zumi/sample/deep-learning-demos/arrow/images/" + str(time.time()) + "." + command + ".jpg"
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            cv2.imwrite(file_name, image)
        else:
            print("# bad command: " + command)
            command = 'start'
        time.sleep(1)
finally:
    clean_up()
