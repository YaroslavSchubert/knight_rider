import time
import serial
import sys,tty,termios

class _Getch:
    def __call__(self):
            fd = sys.stdin.fileno()
            old_settings = termios.tcgetattr(fd)
            try:
                tty.setraw(sys.stdin.fileno())
                ch = sys.stdin.read(3)
            finally:
                termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
            return ch


def getc(serial):
        inkey = _Getch()


        while(1):
                k=inkey()
                if k!='':break
        if k=='\x1b[A':
                print("up")
                serial.write('1'.encode())
        elif k=='\x1b[B':
                print("down")
                serial.write('2'.encode())
        elif k=='\x1b[C':
                print("right")
                serial.write('3'.encode())
        elif k=='\x1b[D':
                print("left")
                serial.write('4'.encode())
        elif k=='sss':
                print("Stop")
                serial.write('S'.encode())
        elif k=='eee':
                print("Exit")
                return
        else:
                print("Key is:", k)
                print("Not an arrow key!")

def main():
        ser = serial.Serial("/dev/ttyUSB0", 9600)
        print("Knight rider initialized")

        for i in range(20):
                getc(ser)

if __name__=='__main__':
        main()