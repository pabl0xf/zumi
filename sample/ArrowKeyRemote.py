import sys
sys.path.insert(0,'/home/pi/zumi/lib')
import Engine as engine
import curses

speed = input("what speed (20-100)?")

# get the curses screen window
screen = curses.initscr()

# turn off input echoing
curses.noecho()

# respond to keys immediately (don't wait for enter)
curses.cbreak()

# map arrow keys to special values
screen.keypad(True)

engine.set_speed(int(speed))

try:
    while True:
        char = screen.getch()
        if char == ord('q'): 
            break
        elif char == curses.KEY_RIGHT:
            # print doesn't work with curses, use addstr instead
            screen.addstr(0, 0, 'right')
            engine.right_a_bit()
        elif char == curses.KEY_LEFT:
            screen.addstr(0, 0, 'left ') 
            engine.left_a_bit()
        elif char == curses.KEY_UP:
            screen.addstr(0, 0, 'up   ') 
            engine.forward_a_bit()
        elif char == curses.KEY_DOWN:
            screen.addstr(0, 0, 'down ')
            engine.back_a_bit()
        
        engine.stop()
finally:
    # shut down cleanly
    curses.nocbreak(); screen.keypad(0); curses.echo()
    curses.endwin()
