import serial
import time
import os

g_serial = None

RPI = True

def init_serial():
    global g_serial
    if RPI:
        usb = None
        for dirname, dirnames, filenames in os.walk('/dev'):
            for filename in filenames:
                file = os.path.join(dirname, filename)
                if not usb:
                    usb = file
                elif 'ttyUSB' in file and file > usb:
                    usb = file

        print("Found USB device: ", usb)
        g_serial = serial.Serial(usb, 9600)
        print(g_serial)
        ack = g_serial.readline()
        print(ack)

def read():
    msg = []
    read = True
    print("Read:")
    while read:
        c = g_serial.read()
        print(c)
        if c == '_':
            read = False
        else:
            msg.append(str(c))
    return "".join(msg)

def send(msg):
    if RPI:
        print("send()")
        g_serial.write(msg.encode())
        g_serial.flushInput()
        print("recv()")

        recv = g_serial.readline()
        # recv = g_serial.read(1)
        recv = str(recv)
        if 'reset' in recv:
            print("recv() [reset detected]")
            recv = g_serial.readline()
            # recv = g_serial.read()
            recv = str(recv)

        print(recv)
        # if 'received' in recv:
        #     print(recv)
        #     print("recv()")
        #     recv = g_serial.readline()
        #     recv = str(recv)
        #     print(recv)
        # else:
        #     print(recv)
