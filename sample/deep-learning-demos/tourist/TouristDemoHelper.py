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

def drive_to_landmark(landmark, model):
    import sys
    sys.path.insert(0,'/home/pi/zumi/lib')
    import Engine as engine
    from IPython import display 
    import cv2
    import numpy as np
    import PIL.Image 
    from TawnTime import FPSTimer
    from TawnCam import PiCamera
    import time

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