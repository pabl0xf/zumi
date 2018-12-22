import sys
sys.path.insert(0,'/home/pi/zumi/src/ZumiV3')
import ZumiV3 as zumi

def turn_on():
    zumi.headlightsOn()

def turn_off():
    zumi.headlightsOff()
