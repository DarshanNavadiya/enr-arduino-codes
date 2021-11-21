import cv2
from keras.models import load_model
import numpy as np
import time
import serial
import threading

# setting up
model = load_model('./basic/keras_model.h5')
arduino = serial.Serial(port='COM3', baudrate=9600)


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

    prev_time = time.time()
    class_index = 'N'
    while ret:
        ret, frame = cap.read()
        cur_time=time.time()

        if cur_time-prev_time >= 2:
            class_index = predict(frame)
            arduino.write(bytes(str(class_index), encoding='utf-8'))
            prev_time = cur_time


        # print('Arduino: ', arduino.readline())
        image = cv2.putText(frame, str(class_index), (50, 50), cv2.FONT_HERSHEY_SIMPLEX,
                            1, (255, 0, 0), 2, cv2.LINE_AA)
        cv2.imshow(windowName, image)
        if cv2.waitKey(1) == 27:
            break

    cv2.destroyAllWindows()

    cap.release()


if __name__ == "__main__":
    main()
