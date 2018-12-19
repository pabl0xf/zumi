import sys
sys.path.insert(0,'/home/pi/zumi/lib')
import Engine as engine
from IPython import display 
import numpy as np
import PIL.Image 
from TawnCam import PiCamera
import time
import cv2

landmarks = {
    'up':0, 'left':1, 'right':2, 
    'nyc':3, 'seattle':4,'eiffel':5,'bigben':6, 'china':7, 'khalifa':8, 'chicago':9, 
    'intersection':10, 'start': 11
}
    
def load_model(which_demo):
    from keras.models import model_from_json
    import json
    
    with open(which_demo + '_model.json') as f:
        json_string = json.load(f)
    model = model_from_json(json_string)

    from keras.models import load_model
    model.load_weights(which_demo + '_weights.h5')

    print("model is loaded 🥂")
    return model

def get_robot_name():
    import socket
    hostname = socket.gethostname() 
    return hostname
    
def take_a_bunch_of_pictures(camera, label):
    cnt = 50
    while cnt >= 0:
        print(cnt)
        cnt = cnt - 1
        image = camera.run()
        image = cv2.flip(image, -1)

        if label not in landmarks:
            print("~invalid label~")
        else:
            file_name = "/home/pi/zumi/sample/deep-learning-demos/tourist/images/" + get_robot_name() + "." + str(time.time()) + "." + label + ".jpg"
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            cv2.imwrite(file_name, image)

def drive_to_landmark(landmark, model):
    timer = FPSTimer()
    camera = PiCamera(image_w=64, image_h=64, image_d=3, framerate=10)

    engine.set_speed(40)

    try:
        while True:

                frame = camera.run()
                timer.on_frame()
                frame = cv2.flip(frame, -1)

                #ask NN to predict control from image
                pred = model.predict(frame[None, :, :, :])

                #get values from pred array
                iArrowDir = np.argmax(pred[0])

                if iArrowDir == 0:
                    command = 'up' 
                    engine.forward()
                elif iArrowDir == 1:
                    command = 'left'
                    engine.left()
                    time.sleep(.1)
                    engine.forward()
                elif iArrowDir == 2:
                    command = 'right' 
                    engine.right()
                    time.sleep(.1)
                    engine.forward()
                elif iArrowDir == 3:
                    command = "nyc"
                elif iArrowDir == 4:
                    command = "seattle"
                elif iArrowDir == 5:
                    command = "eiffel"
                elif iArrowDir == 6:
                    command = "bigben"
                elif iArrowDir == 7:
                    command = "china"
                elif iArrowDir == 8:
                    command = "khalifa"
                elif iArrowDir == 9:
                    command = "chicago"
                    
                if(command == landmark):
                    print("found " + landmark + "!")
                    engine.stop()

                display.clear_output(wait=True)
                display.display(PIL.Image.fromarray(frame))
                display.display(command)

    finally:
        engine.stop()
        camera.shutdown()