from picamera.array import PiRGBArray
import picamera
import cv2

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