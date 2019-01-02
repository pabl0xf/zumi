import math
import time

import Adafruit_SSD1306

from PIL import Image, ImageFont, ImageDraw

# Raspberry Pi pin configuration:
RST = 24
# # Note the following are only used with SPI:
# DC = 23
# SPI_PORT = 0
# SPI_DEVICE = 0

try:
    # 128x64 display with hardware I2C:
    disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST)

    # Initialize library.
    disp.begin()
    width = disp.width
    height = disp.height
    # Clear display.
    disp.clear()
    disp.display()

except:
    print("OLED screen is not connected")


def draw_text(string, x=1, y=1, display=disp, font_size= 40):
    image = Image.new('1', (width, height))
    font = ImageFont.truetype('arial.ttf', font_size)
    draw = ImageDraw.Draw(image)
    max_x = 0
    max_y = 0
    draw.rectangle((0, 0, width, height), outline=0, fill=0)
    current_x = x
    current_y = y
    for char in string:
        char_width, char_height = draw.textsize(char, font=font)
        print(char + ": height-" + str(char_height) + ", width-" + str(char_width))
        max_x = char_width if max_x < char_width else max_x
        max_y = char_height if max_y < char_height else max_y
        draw.text((current_x, current_y), char, font=font, fill=255)
        current_x += char_width
        if current_x > width - max_x:
            current_x = x
            current_y += max_y + 1
    display.image(image)
    display.display()
    #time.sleep(1.5)

def draw_image(img, display=disp):
    display.image(img)
    display.display()

def run():
    landmark = ['NYC', 'Seattle', 'China', 'Eiffel', 'Big Ben']
    while True:
        for land in landmark:
            draw_text(land, font_size=30)
            time.sleep(1.5)


if __name__ == '__main__':
    run()
