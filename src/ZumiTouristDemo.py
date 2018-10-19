#this program reads the serial port
#at a baud rate of 115200
#This code works with Linky

import serial

ser = serial.Serial(
    port = '/dev/ttyUSB0',
    baudrate = 115200,
    parity = serial.PARITY_NONE,
    stopbits = serial.STOPBITS_ONE,
    bytesize = serial.EIGHTBITS,
    timeout = 0.5
    )

def readSensors():
    #FrontLeft,FrontMiddle,FrontRight
    #SBottomLeft,SBottomRight
    #Battery Level
    #Mic level
    ser.write(b'L\n')
    read_serial = ser.readline().decode('utf-8')
    topLeft,topMiddle,topRight,bottomLeft,bottomRight,batterylvl,miclvl = read_serial.split(",")
    return int(topLeft),int(topMiddle),int(topRight),int(bottomLeft),int(bottomRight),float(batterylvl),int(miclvl)

#returns a tuple with the data as integers
def requestData():
    #ON linky only speed is currently requested

    ser.write(b'Z\n')#REQUEST INFO

    read_serial = ser.readline()
    #read the Serial line the rokit should be sending a message

    #chop up that message
    servo1Angle,servo2Angle,servoStep,speed,a19,a20,a21 = read_serial.split(" ")
    #now return the data as integers

    return int(servo1Angle),int(servo2Angle),int(servoStep),int(speed),int(a19),int(a20),int(a21)    

def forward():
    ser.write(b'M\n')

def backward():
    ser.write(b'N\n')

def left():
    ser.write(b'O\n')

def right():
    ser.write(b'P\n')
    
def stop():
    ser.write(b'Q\n')

def speedDecrease():
    ser.write(b'V\n')

def speedIncrease():
    ser.write(b'W\n')

def speed(speedPercentage):
    
    servo1Angle,servo2Angle,servoStep,speed,a19,a20,a21 = requestData()
    currentSpeed = speed
    
    while(currentSpeed > speedPercentage):
        servo1Angle,servo2Angle,servoStep,speed,a19,a20,a21 = requestData()
        currentSpeed = speed
        speedDecrease()
    while(currentSpeed < speedPercentage):
        servo1Angle,servo2Angle,servoStep,speed,a19,a20,a21 = requestData()
        currentSpeed = speed
        speedIncrease()
    
def setSpeed(i):
    ser.write(b'M\n')

def setMotor(i, j):
    """Sets the individual speed of each motor.
    Args: 2 integers, from -100 to 100, for the left and right motors, respectively.
    """
    if i<0:
        i*=-1
        if j<0:
            a = 'C'
            j*=-1
        else:
            a = 'B'
    else:
        if j<0:
            a = 'A'
            j*=-1
        else:
            a = '@'
    a = a + chr(i)
    a = a + chr(j)
    a = a + '\n'
    ser.write(a.encode())

def requestBottomSensorData():
    ser.write(b'R\n')
    read_serial = ser.readline().decode('utf8')
    if read_serial == '':
        return -1
    else:
        return int(read_serial)

def lineTracer():
    ser.write(b'K\n')
    
def beepSad():
    ser.write(b'o\n')
    
def beepHappy():
    ser.write(b'p\n')

def navigate_to_marker(x):
    x%=112
    if x == 1:
      ser.write(b'q\n')
    elif x == 2:
      ser.write(b'r\n')
    else:
      ser.write(b's\n')
