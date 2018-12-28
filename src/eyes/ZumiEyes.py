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

# 128x64 display with hardware I2C:
disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST)

# Initialize library.
disp.begin()

# Clear display.
disp.clear()
disp.display()

EXCITED = {"excited1", "excited2", "excited3"}
EXCITED_LEFT = {"excited_left1", "excited_left2"}
EXCITED_RIGHT = {"excited_right1", "excited_right2"}
LOOK_RIGHT = {"excited_right1", "excited_right2"}
LOOK_LEFT = {"excited_right1", "excited_right2"}
SAD = {"sad_1", "sad_2", "sad_3"}
NEUTRAL = "neutral"

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
    show("blink1")
    show("blink2")
    show("blink3")
    show("blink4")
    
def wake_up():
    show("blink4")
    time.sleep(1)
    show("blink3")
    show("blink2")
    show("blink1")
    time.sleep(5)
    
def blink():
    show("blink1")
    show("blink2")
    show("blink3")
    show("blink4")
    show("blink4")
    show("blink3")
    show("blink2")
    show("blink1")

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
    show("neutral")
    show("sad1")
    show("sad2")
    show("sad3")

    
