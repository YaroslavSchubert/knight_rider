import cv2
from urllib import request
import numpy as np

ip = '192.168.43.77'
stream=request.urlopen('http://{}:8000/stream.mjpg'.format(ip))

bytes=b''
while True:
    bytes+=stream.read(1024)
    a = bytes.find(b'\xff\xd8')
    b = bytes.find(b'\xff\xd9')
    if a!=-1 and b!=-1:
        jpg = bytes[a:b+2]
        bytes= bytes[b+2:]
        i = cv2.imdecode(np.fromstring(jpg, dtype=np.uint8),cv2.IMREAD_COLOR)
        cv2.imshow('i',i)
        if cv2.waitKey(1) ==27:
            exit(0)   
