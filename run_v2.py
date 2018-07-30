import time
import serial
import sys
import tty
import termios


class _Getch:
    def __call__(self):
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch


def getc(serial):
    inkey = _Getch()

    while(1):
        k = inkey()
        if k != '':
            break
    if k == 'w':
        print("up")
        # serial.write('F'.encode())
    elif k == 's':
        print("down")
        # serial.write('B'.encode())
    elif k == 'd':
        print("right")
        # serial.write('R'.encode())
    elif k == 'a':
        print("left")
        # serial.write('L'.encode())
    elif k == 'q':
        print("Stop")
        # serial.write('S'.encode())
    elif k == 'e':
        print("Exit")
        # serial.write('S'.encode())
        return -1
    else:
        print("Key is:", k)
        print("Not an arrow key!")

    return 0


def main():
    ser = None
    # ser = serial.Serial("/dev/ttyUSB0", 9600)
    print("Knight rider initialized")

    while True:
        res = getc(ser)
        if res == -1:
            print("Stopping the machinery!")
            return


if __name__ == '__main__':
    main()
