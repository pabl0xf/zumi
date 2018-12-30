robots = {"whumi": {"left":0, "right":28},
          "newmi": {"left":0, "right":20},
          "pumi": {"left":0, "right":20},
          "kickmi": {"left":0, "right":20},
         }

name = "whumi"

import sys
sys.path.insert(0,'/home/pi/zumi/lib')
import Engine as engine
import curses

# get the curses screen window
screen = curses.initscr()

# turn off input echoing
curses.noecho()

# respond to keys immediately (don't wait for enter)
curses.cbreak()

# map arrow keys to special values
screen.keypad(True)

drive_continuously = False
engine.set_speed(60)
engine.set_left_faster_by(robots.get(name).get("left"))
engine.set_right_faster_by(robots.get(name).get("right"))

try:
    while True:
        char = screen.getch()
        if char == ord('q'): 
            break
        elif char == curses.KEY_RIGHT:
            screen.addstr(0, 0, 'right')
            engine.right_a_bit()
        elif char == curses.KEY_LEFT:
            screen.addstr(0, 0, 'left ') 
            engine.left_a_bit()
        elif char == curses.KEY_UP:
            screen.addstr(0, 0, 'forward ') 
            engine.forward_a_bit()
        elif char == curses.KEY_DOWN:
            screen.addstr(0, 0, 'reverse ')
            engine.back_a_bit()
        elif char == curses.KEY_BACKSPACE:
            screen.addstr(0, 0, 'stop ')
            engine.stop()
            exit()
        
        if drive_continuously:
            engine.forward()
        else:
            engine.stop()

finally:
    # shut down cleanly
    curses.nocbreak(); screen.keypad(0); curses.echo()
    curses.endwin()
