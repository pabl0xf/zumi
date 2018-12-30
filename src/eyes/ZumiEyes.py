# Copyright (c) 2014 Adafruit Industries
# Author: Tony DiCola
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
import time

import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306

from PIL import Image

# Raspberry Pi pin configuration:
RST = 24

try: 
    # 128x64 display with hardware I2C:
    disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST)

    # Initialize library.
    disp.begin()

    # Clear display.
    disp.clear()
    disp.display()

except:
    print("OLED screen is not connected!")

EXCITED = {"excited1", "excited2", "excited3"}
LOOK_RIGHT = {"big_eyes1", "big_eyes1"} #don't have designs for these yet
LOOK_LEFT = {"big_eyes1", "big_eyes1"}  #don't have designs for these yet
NEUTRAL = "big_eyes1"

import time
def animate(images):
    for frame in images:
        image = Image.open("/home/pi/zumi/src/eyes/images/" + frame + ".ppm").convert('1')
        disp.image(image)
        disp.display()

def show(frame):
    image = Image.open("/home/pi/zumi/src/eyes/images/" + frame + ".ppm").convert('1')
    disp.image(image)
    disp.display()
    
def close_eyes():    
    show("big_eyes1")
    time.sleep(.5)
    show("sleep")
    
def wake_up():
    show("blink4")
    time.sleep(1)
    show("blink3")
    show("blink2")
    show("blink1")
    time.sleep(5)
    
def blink():
    show("big_eyes1")
    time.sleep(.25)
    show("sleep")
    time.sleep(.25)
    show("opening_1")
    show("big_eyes1")

def blink2():
    show("blinking_1")
    show("blinking_2")
    show("blinking_3")
    show("blinking_2")
    show("blinking_1")

def glimmer():
    show("big_eyes1")
    show("big_eyes2")
    show("big_eyes3")

def sad():    
    show("sad1")
    show("sad2")
    show("sad3")

def happy():
    show("big_eyes1")
    show("happy_1")
    show("happy_left2")
    show("happy_right1")
    show("happy_left2")
    show("happy_right1")
    show("happy_left2")
    show("happy_right1")
    show("opening_1")

