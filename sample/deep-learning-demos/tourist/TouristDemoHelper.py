import sys
sys.path.insert(0,'/home/pi/zumi/lib')
import Engine as engine
import Eyes as eyes
from IPython import display 
import numpy as np
import PIL.Image 
from TawnCam import PiCamera
import time
import cv2

landmarks = {
    0: 'up', 1: 'left', 2:'right', 3:'nyc', 4:'china', 5:'eiffel', 
    #6:'bigben', 7:'seattle', 8:'khalifa', 9:'chicago', 
    #10:'intersection', 11:'start'
}

speed = 40
    
def load_model(which_demo):
    eyes.hello()
    from keras.models import model_from_json
    import json
    
    with open("/home/pi/zumi/sample/deep-learning-demos/tourist/" + which_demo + '_model.json') as f:
        json_string = json.load(f)
    model = model_from_json(json_string)

    from keras.models import load_model
    model.load_weights("/home/pi/zumi/sample/deep-learning-demos/tourist/" + which_demo + '_weights.h5')

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
    engine.set_speed(speed)
    
    if direction == "up":
        engine.forward_a_bit()
    elif direction == 'left':
        engine.left_a_bit(get_robot_name())
    elif direction == "right":
        engine.right_a_bit()
    elif direction != None:
        engine.forward_a_bit() 
        
def drive_to_landmark(landmark, model):
    camera = PiCamera(image_w=64, image_h=64, image_d=3, framerate=10)

    try:
        while True:

                frame = camera.run()
                frame = cv2.flip(frame, -1)

                #ask NN to predict control from image
                pred = model.predict(frame[None, :, :, :])

                #get values from pred array
                iArrowDir = np.argmax(pred[0])
                command = landmarks.get(iArrowDir)
                
                display.clear_output(wait=True)
                display.display(command)
                display.display(get_readable_predictions(pred))
                
                drive_and_continue(command)
                    
                if(command == landmark):
                    engine.stop()
                    time.sleep(5)
#                     confidence = pred[0][iArrowDir]
# #                         print("found " + command + " with confidence: " + str(confidence))
#                     if command == "china" and confidence < .82:
#                         x=1
# #                             print("FAKE CHINA ")
#                     elif command == "nyc" and confidence < .9: 
# #                             print("FAKE NEW YORK ")  ?
#                         x=1
#                     else:
#                         engine.stop()
#                         time.sleep(5)
                        

    finally:
        engine.stop()
        camera.shutdown()
        
        
def calibrate_motors():
    robots = {"whumi": {"left":0, "right":28},
          "newmi": {"left":0, "right":20},
          "pumi": {"left":0, "right":20},
          "kickmi": {"left":0, "right":20},
    }
    engine.set_speed(50)
    engine.set_left_faster_by(robots.get(get_robot_name()).get("left"))
    engine.set_right_faster_by(robots.get(get_robot_name()).get("right"))