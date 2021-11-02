import cv2
from keras.models import load_model
from PIL import Image, ImageOps
import numpy as np
import time
import serial

# setting up
model = load_model('./basic/keras_model.h5')
arduino = serial.Serial(port='COM5', baudrate=9600)


def predict(image):
    data = np.ndarray(shape=(1, 224, 224, 3), dtype=np.float32)

    size = (224, 224)
    image_array = cv2.resize(image, dsize=size, interpolation=cv2.INTER_CUBIC)

    normalized_image_array = (image_array.astype(np.float32) / 127.0) - 1
    data[0] = normalized_image_array

    predictions = model.predict(data)
    return np.argmax(predictions[0])


def main():
    windowName = "Live Video Feed"
    # Load Model
    cv2.namedWindow(windowName)
    cap = cv2.VideoCapture(0)

    if cap.isOpened():
        ret, frame = cap.read()
    else:
        ret = False

    while ret:

        ret, frame = cap.read()
        class_index = predict(frame)
        arduino.write(bytes(str(class_index), encoding='utf-8'))
        print('Arduino: ', arduino.readline())

        cv2.imshow(windowName, frame)
        if cv2.waitKey(1) == 27:
            break

    cv2.destroyAllWindows()

    cap.release()


if __name__ == "__main__":
    main()
