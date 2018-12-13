#Import this file to use all of the functions necessary to move Linky
import time
import sys
sys.path.insert(0,'/home/pi/zumi/src/ZumiV3/')
import ZumiV3 as zumi

def forward():
    zumi.forward()

def stop():
    zumi.stop()

def reverse():
    zumi.backward()

def right_a_bit():
    zumi.right()
    time.sleep(.1)

def left_a_bit():
    zumi.left()
    time.sleep(.1)

def forward_a_bit():
    zumi.forward()
    time.sleep(.6)

def set_speed(s):
    zumi.setSpeed(s)

def left():
    zumi.left()

def right():
    zumi.right()