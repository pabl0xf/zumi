import sys
sys.path.insert(0,'/home/pi/zumi/src/ZumiV3')
import ZumiV3 as zumi

def jedi_drive():
    print("Use the force to move Zumi from behind!")
    zumi.beginJediDrive()
