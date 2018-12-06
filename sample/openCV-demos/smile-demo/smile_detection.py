from picamera.array import PiRGBArray
import picamera
import cv2
import os

def smile_detected():
    
    face_detector = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
        
    with picamera.PiCamera() as camera:
        camera.resolution = (640, 480)
        with picamera.array.PiRGBArray(camera) as stream:
            camera.capture(stream, format='bgr')
            image = stream.array

#             gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) might work better with this?

            faces = face_detector.detectMultiScale(image, 1.3, 5)
    
            if type(faces) is not tuple:
                for(x, y, w, h) in faces:
                    image = image[y:y+h, x:x+w]
                    smile_detector = cv2.CascadeClassifier('haarcascade_smile.xml')
                    #gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
                
                    smiles = smile_detector.detectMultiScale(image, 1.7, 22)
                
                    if type(smiles) is not tuple:
                        number = len(os.listdir('./faces/smiles')) + 1
                        cv2.imwrite('./faces/smiles/smile_' + str(number) +'.jpg', image)
                        return True
                    else:
                        number = len(os.listdir('./faces/not_smiles')) + 1
                        cv2.imwrite('./faces/not_smiles/not_smiles_' + str(number) +'.jpg', image)
                        return False
            else:
                return False

def take_photo():
    with picamera.PiCamera() as camera:
        camera.capture("your-face.jpg")
  
