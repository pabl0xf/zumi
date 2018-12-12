import smbus

bus = smbus.SMBus(1)
address = 0x04

def beginJediDrive():
    try:
        bus.write_byte(address, 83)
    except IOError:
        return beginJediDrive()
