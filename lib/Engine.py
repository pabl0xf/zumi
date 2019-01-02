from __future__ import division
import time
import sys
sys.path.insert(0,'/home/pi/zumi/src/ZumiV3/')
import ZumiV3 as zumi

speed = 50
right_faster_by = 0
left_faster_by = 0
zumi.disableAcceleration()

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
    zumi.engage_motors(right_speed, left_speed)

def stop():
    zumi.stop()

def reverse():
    zumi.backward()

def right_a_bit_OLD():
    zumi.right()
    time.sleep(.1)
    
def right_a_bit():   
    left_speed = speed
    right_speed = speed
    right_speed = speed + speed/100*right_faster_by
    left_speed = speed + speed/100*left_faster_by
    zumi.engage_motors(right_speed, -left_speed)
    time.sleep(.1)

def left_a_bit():
    left_speed = speed
    right_speed = speed
    right_speed = speed + speed/100*right_faster_by
    left_speed = speed + speed/100*left_faster_by
    zumi.engage_motors(-right_speed, left_speed)
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
    
def calibrate_motors_for_tourist_demo():
    robots = {"whumi": {"left":0, "right":28},
          "newmi": {"left":0, "right":20},
          "pumi": {"left":-2, "right":25},
          "kickmi": {"left":0, "right":20},
         }
    set_speed(70)
    set_left_faster_by(robots.get(get_robot_name()).get("left"))
    set_right_faster_by(robots.get(get_robot_name()).get("right"))
    
def get_robot_name():
    import socket
    hostname = socket.gethostname() 
    return hostname