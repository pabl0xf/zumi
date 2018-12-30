import sys
sys.path.insert(0,'/home/pi/zumi/lib')
import Engine as engine
import Speaker as speaker
import Lights as lights
import Eyes as eyes
import Timer as timer

def happy_zumi():
#     speaker.play_happy_sound()
    eyes.happy()
    lights.turn_on()
    time.sleep(.5)
    engine.set_speed(30)
    engine.left_a_bit()
    engine.right_a_bit()
    engine.left_a_bit()
    engine.right_a_bit()
    engine.left_a_bit()
    engine.right_a_bit()
    lights.turn_off()
    engine.stop()
#     speaker.play_happy_sound()
    
def sad_zumi():
    sys.path.insert(0,'/home/pi/zumi/src/ZumiV3/')
    import ZumiV3 as zumi

    baseline_speed = 15
    speed_difference = 20
    curve_duration = .7
    
    eyes.sad()

    faster = baseline_speed+speed_difference
    slower = baseline_speed
    zumi.setMotor(-faster, -slower)
    time.sleep(curve_duration)
    zumi.setMotor(-slower, -faster)
    time.sleep(curve_duration)
    engine.stop()
   
#     speaker.play_sad_sound()
    
def excited_zumi():
    eyes.hello()
    engine.set_speed(100)
    engine.right()
    timer.wait(1.6)
    engine.stop()
    eyes.excited()
    eyes.hello()
    
excited_zumi()