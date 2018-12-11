import sys
sys.path.insert(0,'/home/pi/zumi/lib')
from TawnCam import PiCamera
import cv2

print("loading camera...")
camera = PiCamera(image_w=300, image_h=300, image_d=3, framerate=10)

def face_detected():
    face_detector = cv2.CascadeClassifier('/home/pi/zumi/sample/openCV-demos/face_detection/haarcascade_frontalface_default.xml')
    image = camera.run()
    image = cv2.flip(image, -1)
    faces = face_detector.detectMultiScale(image, 1.3, 5)
    return type(faces) is not tuple

def take_photo():
    image = camera.run()
    cv2.imwrite("your-face.jpg", image)
    show();
        
def show():
    from IPython import display 
    import PIL.Image 
    image = camera.run()
    image = cv2.flip(image, -1)
    display.clear_output(wait=True)
    display.display(PIL.Image.fromarray(image))
