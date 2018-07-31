import argparse

import cv2 as cv
import numpy as np
import imutils

ap = argparse.ArgumentParser()
ap.add_argument("-c", "--config", required=True,
                help="Model configuration file")
ap.add_argument("-m", "--model", required=True, help="Model file")

args = vars(ap.parse_args())

CLASSES = ["background", "aeroplane", "bicycle", "bird", "boat",
           "bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
           "dog", "horse", "motorbike", "person", "pottedplant", "sheep",
           "sofa", "train", "tvmonitor"]
COLORS = np.random.uniform(0, 255, size=(len(CLASSES), 3))

# config

SCALE_FACTOR = 2/255
MEAN = 127.5
INPUT_WIDTH = 1280
INPUT_HEIGHT = 720
FRAME_SIZE = (300, 300)
THRESHOLD = 0.5

# load model
net = cv.dnn.readNetFromCaffe(args["config"], args["model"])


# Process stream

cap = cv.VideoCapture(0)

while cv.waitKey(1) < 0:
    hasFrame, frame = cap.read()
    if not hasFrame:
        cv.waitKey()
        break

    # frame = cv.resize(frame, (INPUT_WIDTH, INPUT_HEIGHT, 3))
    frame = imutils.resize(frame, width=400)
    h, w = frame.shape[:2]
    img_blob = cv.dnn.blobFromImage(frame, SCALE_FACTOR, FRAME_SIZE, MEAN)

    net.setInput(img_blob)
    detections = net.forward()

    for i in range(0, detections.shape[2]):
        confidence = detections[0, 0, i, 2]

        if confidence > THRESHOLD:
            idx = int(detections[0, 0, i, 1])

            # compute absolute coordinates
            box = detections[0, 0, i, 3:7] * np.array([w, h, w, h])
            x1, y1, x2, y2 = box.astype('int')

            # draw predictions
            label = "{}:{}".format(CLASSES[idx], confidence)
            cv.rectangle(frame, (x1, y1), (x2, y2), COLORS[idx], 2)
            cv.putText(frame, label, (x1, y1),
                       cv.FONT_HERSHEY_SIMPLEX, 0.5, COLORS[idx], 2)

    cv.imshow("winName", frame)
