import sys
sys.path.insert(0,'/home/pi/zumi/src/ZumiV3/')
import ZumiV3 as linky
import time

def get_front_distance():
   # time.sleep(.2)
    topLeft, topMiddle, topRight, bottomLeft, bottomRight, batterylvl, miclvl = linky.readSensors()
    return topMiddle

def get_left_distance():
   # time.sleep(.2)
    topLeft, topMiddle, topRight, bottomLeft, bottomRight, batterylvl, miclvl = linky.readSensors()
    return topLeft

def get_right_distance():
   # time.sleep(.2)
    topLeft, topMiddle, topRight, bottomLeft, bottomRight, batterylvl, miclvl = linky.readSensors()
    return topRight

def get_bottom_left():
   # time.sleep(.2)
    topLeft, topMiddle, topRight, bottomLeft, bottomRight, batterylvl, miclvl = linky.readSensors()
    return bottomLeft

def get_bottom_right():
   # time.sleep(.2)
    topLeft, topMiddle, topRight, bottomLeft, bottomRight, batterylvl, miclvl = linky.readSensors()
    return bottomRight

def get_bottom_colors():
    return linky.requestBottomSensorData()
   
def get_bottom_left_color():
    topLeft, topMiddle, topRight, bottomLeft, bottomRight, batterylvl, miclvl = linky.readSensors()
    if bottomLeft > 960 and bottomLeft < 1005:
        return "black"
    elif bottomLeft > 840 and bottomLeft < 895:
        return "white"
