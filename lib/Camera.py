import sys
sys.path.insert(0,'/home/pi/zumi/lib')
from TawnCam import PiCamera
import cv2

camera = PiCamera(image_w=64, image_h=64, image_d=3, framerate=10)

def face_detected():
    
    face_detector = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
        
    with picamera.PiCamera() as camera:
        camera.resolution = (224, 192)
        with picamera.array.PiRGBArray(camera) as stream:
            camera.capture(stream, format='bgr')
            image = stream.array

#             gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) might work better with this?

            faces = face_detector.detectMultiScale(image, 1.3, 5)

            return type(faces) is not tuple

def take_photo():
    with picamera.PiCamera() as camera:
        camera.capture("your-face.jpg")
        
def show():
    from IPython import display 
    image = camera.run()

#                 frame = cv2.flip(frame, -1)
    display.clear_output(wait=True)
    display.display(PIL.Image.fromarray(frame))
