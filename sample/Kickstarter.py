import sys
sys.path.insert(0,'/home/pi/zumi/lib')
import Engine as engine
import Eyes as eyes
import curses
import time



# get the curses screen window
screen = curses.initscr()

# turn off input echoing
curses.noecho()

# respond to keys immediately (don't wait for enter)
curses.cbreak()

# map arrow keys to special values
screen.keypad(True)

engine.set_speed(45)
engine.calibrate_motors_for_tourist_demo()

try:
    while True:
        eyes.hello()
        char = screen.getch()
        if char == ord('q'): 
            break
        elif char == curses.KEY_RIGHT:
            screen.addstr(0, 0, 'right')
#             engine.right_a_bit()
            engine.right()
#             time.sleep(.05)
#             engine.forward()
        elif char == curses.KEY_LEFT:
            screen.addstr(0, 0, 'left ') 
#             engine.left_a_bit()
            engine.left()
#             time.sleep(.05)
#             engine.forward()
        elif char == curses.KEY_UP:
            screen.addstr(0, 0, 'forward   ') 
            engine.forward()
        elif char == curses.KEY_DOWN:
            screen.addstr(0, 0, 'reverse ')
            engine.stop()
            eyes.blink()
        elif char == curses.KEY_BACKSPACE:
            screen.addstr(0, 0, 'stop ')
            engine.stop
            


finally:
    # shut down cleanly
    curses.nocbreak(); screen.keypad(0); curses.echo()
    curses.endwin()
