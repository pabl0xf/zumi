import sys
sys.path.insert(0,'/home/pi/zumi/lib')
from TawnCam import PiCamera
import cv2

print("loading camera...")
camera = PiCamera(image_w=400, image_h=400, image_d=3, framerate=10)

def face_detected():
    face_detector = cv2.CascadeClassifier('/home/pi/zumi/sample/openCV-demos/face_detection/haarcascade_frontalface_default.xml')
    image = camera.run()
    image = cv2.flip(image, -1)
    faces = face_detector.detectMultiScale(image, 1.3, 5)
    return type(faces) is not tuple

# def face_detected_old():
    
#     face_detector = cv2.CascadeClassifier('/home/pi/zumi/sample/haarcascade_frontalface_default.xml')
        
# #     with .PiCamera() as camera:
#         with picamera.array.PiRGBArray(camera) as stream:
#             camera.capture(stream, format='bgr')
#             image = stream.array

# #             gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) might work better with this?

#             faces = face_detector.detectMultiScale(image, 1.3, 5)

#             return type(faces) is not tuple

def take_photo():
    image = camera.run()
    cv2.imwrite(image, "your-face.jpg")
    show();
        
def show():
    from IPython import display 
    import PIL.Image 
    image = camera.run()
    image = cv2.flip(image, -1)
    display.clear_output(wait=True)
    display.display(PIL.Image.fromarray(image))
