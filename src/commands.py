from enum import Enum

from communication import send

class CMD(Enum):
    STOP = 1
    FORWARD = 2
    BACKWARD = 3
    TURN_LEFT = 4
    TURN_RIGHT = 5
    MAX_STOP = 6
    MAX_FORWARD = 7
    MAX_BACKWARD = 8
    MAX_TURN_LEFT = 9
    MAX_TURN_RIGHT = 10
    MOTORS_SELECT_ALL = 11
    MOTORS_SELECT_1 = 12
    MOTORS_SELECT_2 = 13
    MOTORS_SELECT_3 = 14
    MOTORS_SELECT_4 = 15
    SAVE_MAX = 16
    RESET_MAX = 17
    ENGINE_ON = 18
    ENGINE_OFF = 19
    MOTORS_SELECT_5 = 20
    MOTORS_SELECT_6 = 21


def command(cmd):
    if cmd == CMD.STOP:
        print(cmd)
        send('s')
    elif cmd == CMD.FORWARD:
        print(cmd)
        send('f')
    elif cmd == CMD.BACKWARD:
        print(cmd)
        send('b')
    elif cmd == CMD.TURN_LEFT:
        print(cmd)
        send('l')
    elif cmd == CMD.TURN_RIGHT:
        print(cmd)
        send('r')
    elif cmd == CMD.MAX_STOP:
        print(cmd)
        send('S')
    elif cmd == CMD.MAX_FORWARD:
        print(cmd)
        send('F')
    elif cmd == CMD.MAX_BACKWARD:
        print(cmd)
        send('B')
    elif cmd == CMD.MAX_TURN_LEFT:
        print(cmd)
        send('L')
    elif cmd == CMD.MAX_TURN_RIGHT:
        print(cmd)
        send('R')
    elif cmd == CMD.MOTORS_SELECT_ALL:
        print(cmd)
        send('0')
    elif cmd == CMD.MOTORS_SELECT_1:
        print(cmd)
        send('1')
    elif cmd == CMD.MOTORS_SELECT_2:
        print(cmd)
        send('2')
    elif cmd == CMD.MOTORS_SELECT_3:
        print(cmd)
        send('3')
    elif cmd == CMD.MOTORS_SELECT_4:
        print(cmd)
        send('4')
    elif cmd == CMD.MOTORS_SELECT_5:
        print(cmd)
        send('5')
    elif cmd == CMD.MOTORS_SELECT_6:
        print(cmd)
        send('6')
    elif cmd == CMD.SAVE_MAX:
        print(cmd)
        send('u')
    elif cmd == CMD.RESET_MAX:
        print(cmd)
        send('U')
    elif cmd == CMD.ENGINE_ON:
        print(cmd)
        send('e')
    elif cmd == CMD.ENGINE_OFF:
        print(cmd)
        send('E')
