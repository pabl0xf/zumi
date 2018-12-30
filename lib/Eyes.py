import sys
sys.path.insert(0,'/home/pi/zumi/src/eyes/')
import ZumiEyes as eyes

def sleep():    
    eyes.close_eyes()
    
def wake_up():
    eyes.wake_up()
    
def blink():
    eyes.blink()
    
def excited():
    eyes.animate(eyes.EXCITED)
    
def look_left():
    eyes.animate(eyes.LOOK_LEFT)
    
def look_right():
    eyes.animate(eyes.LOOK_RIGHT)
    
def sad():
    eyes.sad()
    
def hello():
    try:
        eyes.show(eyes.NEUTRAL)
    except:
        print("OLED screen is not connected!")
    
def glimmer():
    eyes.glimmer()
    
def happy():
    eyes.happy()