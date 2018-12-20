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
    0: 'up', 1: 'left', 2:'right', 3:'nyc', 4:'seattle', 5:'eiffel', 6:'bigben', 7:'china', 8:'khalifa', 9:'chicago', 
    10:'intersection', 11:'start'
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
    cnt = 20
    while cnt >= 0:
        print(cnt)
        cnt = cnt - 1
        image = camera.run()
        image = cv2.flip(image, -1)

        if label not in landmarks.values():
            print("~invalid label~")
        else:
            file_name = "/home/pi/zumi/sample/deep-learning-demos/tourist/images/" + get_robot_name() + "." + str(time.time()) + "." + label + ".jpg"
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            cv2.imwrite(file_name, image)
            
def get_readable_predictions(predictions):
    stringy= ""
    for index in landmarks:
        stringy = stringy + landmarks.get(index) + " {:.2%}".format(predictions[0][index]) + "  "
    return stringy

def drive_and_stop(direction):
     drive(direction)
     engine.stop()
    
def drive_and_continue(direction):
    drive(direction)
    engine.forward()
    
def drive(direction):
    if direction == "up":
        engine.forward_a_bit()
    elif direction == 'left':
        engine.left_a_bit()
    elif direction == "right":
        engine.right_a_bit()
    else:
        engine.forward_a_bit()        

def drive_to_landmark(landmark, model):
    camera = PiCamera(image_w=64, image_h=64, image_d=3, framerate=10)

    engine.set_speed(40)

    try:
        while True:

                frame = camera.run()
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