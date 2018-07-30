import time
import serial
if __name__ == '__main__':
        ser = serial.Serial("/dev/ttyUSB0", 9600)
        time.sleep(2)
        print('Go Raspberry, GO!')
        while True:
            ser.write('F'.encode())
            time.sleep(2)
            ser.write('S'.encode())
            time.sleep(2)
            print('Wrrrrruuuuunnnnnn!! \n')

