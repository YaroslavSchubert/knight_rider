import time
import serial
if __name__ == '__main__':
        ser = serial.Serial("/dev/ttyUSB0", 9600)
        print('Go Raspberry, GO!')
        while True:
            print('Wrunnn left!! \n')
            #ser.write('F'.encode())
            ser.write('L'.encode())
            time.sleep(5)

            ser.write('S'.encode())
            time.sleep(2)

