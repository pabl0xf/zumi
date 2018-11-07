#Import this file to use all of the functions necessary to move Linky
import time
import sys
sys.path.insert(0,'/home/pi/zumi/src')
import ZumiV3 as zumi

def go_forward():
    zumi.forward()
    print("Forward")

def stop():
    zumi.stop()
    print("Stop")

def go_backward():
    zumi.backward()
    print("Backward")

def right_a_bit():
    zumi.setMotor(10, -5)
    time.sleep(.1)
    zumi.stop()

def left_a_bit():
    zumi.setMotor(-5, 10)
    time.sleep(.1)
    zumi.stop()

def forward_a_bit():
    zumi.setMotor(20, 20)
    time.sleep(.3)
    zumi.stop()

def set_speed(s):
    zumi.setSpeed(s)
    print("Speed = "+str(s))

def keep_turning_left():
    zumi.left()
    print("Left")

def keep_turning_right():
    zumi.right()
    print("Right")