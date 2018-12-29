#Import this file to use all of the functions necessary to move Linky
import time
import sys
sys.path.insert(0,'/home/pi/zumi/src/ZumiV3/')
import ZumiV3 as zumi

speed = 50
right_faster_by = 0
left_faster_by = 0

def set_right_faster_by(percentage_increase):
    global right_faster_by
    right_faster_by = percentage_increase

def set_left_faster_by(percentage_increase):
    global left_faster_by 
    left_faster_by = percentage_increase

def forward():
    left_speed = speed
    right_speed = speed
    right_speed = speed + speed/100*right_faster_by
    left_speed = speed + speed/100*left_faster_by
    zumi.engage_motors(left_speed, right_speed)

def stop():
    zumi.stop()

def reverse():
    zumi.backward()

def right_a_bit():
    zumi.right()
    time.sleep(.1)

def left_a_bit(robot_name="zumi"):
    zumi.left()
    if robot_name == "whumi":
        time.sleep(.2)
    elif robot_name =="pumi":
        time.sleep(.2)
    else:
        time.sleep(.1)

def forward_a_bit():
    forward()
    time.sleep(.6)
    
def back_a_bit():
    zumi.backward()
    time.sleep(.1)

def set_speed(s):
    global speed
    speed = s
    zumi.setSpeed(s)

def left():
    zumi.left()

def right():
    zumi.right()