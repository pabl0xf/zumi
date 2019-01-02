import sys
sys.path.insert(0,'/home/pi/zumi/lib')
import Engine as engine
import time

engine.set_speed(30)
engine.set_left_faster_by(15)

engine.forward()
time.sleep(1)
engine.stop()

