import smbus
import time

bus = smbus.SMBus(1)
address = 0x04

def forward():
    try:
        bus.write_byte(address, 77)
    except IOError:
        return forward()

def backward():
    try:
        bus.write_byte(address, 78)
    except IOError:
        return backward()

def left():
    try:
        bus.write_byte(address, 79)
    except IOError:
        return left()

def right():
    try:
        bus.write_byte(address, 80)
    except IOError:
        return right()

def stop():
    try:
        bus.write_byte(address, 81)
    except IOError:
        return stop()

def setMotor(i, j):
    """Sets the individual speed of each motor.
    Args: 2 integers, from -100 to 100, for the left and right motors, respectively.
    """
    try:
        if i<0:
            i=-i
            if j<0:
                a = 67
                j=-j
            else:
                a = 66
        else:
            if j<0:
                a = 65
                j=-j
            else:
                a = 64
        if i>100:
            i = 100
        if j>100:
            j = 100
        bus.write_i2c_block_data(address, a, [int(i), int(j)])
    except IOError:
        return setMotor(i, j)

def setSpeed(i):
    try:
        if i < 0:
            i = 0
        if i > 100:
            i = 100
        bus.write_byte_data(address, 70, int(i))
    except IOError:
        return setSpeed(i)

def playExcited():
    try:
        bus.write_byte(address, 82)
    except IOError:
        return playExcited()

def beginJediDrive():
    try:
        bus.write_byte(address, 83)
    except IOError:
        return beginJediDrive()
