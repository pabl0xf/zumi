import sys
sys.stdout.write('loading camera.')

sys.path.insert(0,'/home/pi/zumi/lib')
from TawnCam import PiCamera
import cv2

sys.stdout.write('.')

camera = PiCamera(image_d=3, framerate=10)

sys.stdout.write('.')

def face_detected():
    face_detector = cv2.CascadeClassifier('/home/pi/zumi/sample/openCV-demos/face_detection/haarcascade_frontalface_default.xml')
    image = camera.run()
    image = cv2.flip(image, -1)
    faces = face_detector.detectMultiScale(image, 1.3, 5)
    return type(faces) is not tuple

def take_photo():
    import os
#     camera.set_resolution(640, 480)
    image = camera.run()
    image = cv2.flip(image, -1)
    file_name = "zumi-snap.jpg"
    cv2.imwrite(file_name, image)
    show();
    print("Saved photo at: " + os.getcwd() + "/" + file_name)
        
def show():
    from IPython import display 
    import PIL.Image 
    image = camera.run()
    image = cv2.flip(image, -1)
    display.clear_output(wait=True)
    display.display(PIL.Image.fromarray(image))
