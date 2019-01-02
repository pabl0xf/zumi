from picamera.array import PiRGBArray
from picamera import PiCamera
import numpy as np
import cv2
from PIL import Image
from keras.models import Sequential
from keras.layers import Conv2D, MaxPooling2D, Activation, Flatten, Dense, Dropout, LeakyReLU
from keras.preprocessing.image import img_to_array
from keras import backend as K
import time
import zumi_eye_text as eye
from crop import Crop

# set input resolution
WIDTH = 64
HEIGHT = 64
landmark = ['Big Ben', 'China', 'NYC', 'Paris', 'Seattle']

if K.image_data_format() == 'channels_first':
    input_shape = (3, WIDTH, HEIGHT)
else:
    input_shape = (WIDTH, HEIGHT, 3)

weight_file = '/home/pi/zumi/ces-demo/weights-whoseop_crop2.hdf5'

def generate_calssification_model(filen = weight_file):
    model = Sequential()
    model.add(Conv2D(32, kernel_size=(3, 3),
                     activation='relu',
                     input_shape=(64, 64, 3)))
    model.add(Conv2D(64, (3, 3), activation='relu'))
    model.add(Dropout(0.1))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Conv2D(64, (3, 3), activation='relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Flatten())
    model.add(Dense(128, activation='relu'))
    model.add(Dropout(0.1))
    model.add(Dense(5, activation='softmax'))

    model.load_weights(filen)
    # compile
    model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
    print(filen)
    return model


def predict(model, w=WIDTH, h=HEIGHT):
    c = Crop()
    # set up camera
    camera = PiCamera()
    camera.resolution = (w, h)
    camera.framerate = 32
    raw_capture = PiRGBArray(camera, size=(w, h))
    # let camera warm up
    time.sleep(0.1)
    cnt = 0
    cnt_label = 0
    try:
        # take video stream
        for frame in camera.capture_continuous(raw_capture, format="bgr", use_video_port=True):
            # take frame
            img = frame.array
            img = cv2.flip(img, -1)
            #cv2.imshow("window", img)
            #gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            crop_img = c.crop(img)
            if crop_img is None:
                raw_capture.truncate(0)
                continue
            cv2.imshow("ss",crop_img)
            #cv2.imshow("ss",img)
            #gray = cv2.resize(gray, (128, 64))
            x = Image.fromarray(crop_img)
            #x = Image.fromarray(img)
            x = np.expand_dims(x, axis=0)

            pred = model.predict(x)
            preds = model.predict_classes(x)
            #print(pred, preds)
            print(landmark[preds[0]])
            #eye.draw_text(landmark[preds[0]])
            #eye.draw_image(Image.fromarray(gray).convert('1'))
            
            # clear camera buffer
            raw_capture.truncate(0)
            if cnt_label == preds[0]:
                cnt += 1
                if cnt > 100:
                    camera.close()
                    return landmark[preds[0]]
            else:
                cnt = 0
                cnt_label = preds[0]
            # keyboard control
            key = cv2.waitKey(1) & 0xFF
            if key == ord("q"):
                break

    except KeyboardInterrupt:
        print("\nExiting...")


def run():
    print("init run method")
    classification_model = generate_calssification_model("weights-whoseop_crop.hdf5")
    print("generate model")
    land = predict(classification_model)
    #print(land + " :  finish")

if __name__ == "__main__":
    run()
