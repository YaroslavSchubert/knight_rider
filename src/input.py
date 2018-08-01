import time
# import serial
import sys
import tty
import termios

from keypress import keypress

DEBUG = False

def stdin_read_char():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch


def input_read(serial=None):
    reading = True
    # Arrows are composed of three chars: 1b, [, arrow
    # Ctrl+Arrows are composed of three chars: ;, 5, arrow
    is_arrow = 0
    is_ctrl_arrow = 0
    while (reading):
        if is_arrow == 0:
            print("input:")
        c = stdin_read_char()

        if DEBUG:
            print(repr(c))

        key = None
        if c == chr(3): # Ctrl-C
            reading = False
        elif c == '\x00':
            key = 'ctrl- '
        elif c == '\x17':
            key = 'ctrl-w'
        elif c == '\x13':
            key = 'ctrl-s'
        elif c == '\x01':
            key = 'ctrl-a'
        elif c == '\x04':
            key = 'ctrl-d'
        elif c == '\x1b' and is_arrow == 0:
            is_arrow = 1
        elif c == '[' and is_arrow == 1:
            is_arrow = 2
        elif c == ';' and is_ctrl_arrow == 0:
            is_ctrl_arrow = 1
        elif c == '5' and is_ctrl_arrow == 1:
            is_ctrl_arrow = 2
        elif is_arrow == 2 or is_ctrl_arrow == 2:
            if c == 'A':
                key = 'up'
            elif c == 'B':
                key = 'down'
            elif c == 'D':
                key = 'left'
            elif c == 'C':
                key = 'right'
            if is_ctrl_arrow == 2:
                key = 'ctrl-' + key

            is_arrow = 0
            is_ctrl_arrow = 0
        else:
            key = c

        if key:
            if DEBUG:
                print("keypress: ", key)
            reading = keypress(key)

