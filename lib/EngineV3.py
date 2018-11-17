#Import this file to use all of the functions necessary to move Linky
import time
import sys
sys.path.insert(0,'/home/pi/zumi/src/ZumiV3/')
import ZumiV3 as zumi

def go_forward():
    zumi.forward()

def stop():
    zumi.stop()

def go_backward():
    zumi.backward()

def right_a_bit():
#     zumi.setSpeed(30)
    zumi.right()
    time.sleep(.1)
#     zumi.stop()

def left_a_bit():
#     zumi.setSpeed(30)
    zumi.left()
    time.sleep(.1)
#     zumi.stop()

def forward_a_bit():
    zumi.setSpeed(40)
    zumi.forward()
    time.sleep(.8)
    zumi.stop()

def set_speed(s):
    zumi.setSpeed(s)
    print("Speed = "+str(s))

def keep_turning_left():
    zumi.left()
#     print("Left")

def keep_turning_right():
    zumi.right()
#     print("Right")