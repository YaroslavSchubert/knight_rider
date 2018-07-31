from enum import Enum


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


def command(cmd):
    if cmd == CMD.STOP:
        print(cmd)
    elif cmd == CMD.FORWARD:
        print(cmd)
    elif cmd == CMD.BACKWARD:
        print(cmd)
    elif cmd == CMD.TURN_LEFT:
        print(cmd)
    elif cmd == CMD.TURN_RIGHT:
        print(cmd)
    elif cmd == CMD.MAX_STOP:
        print(cmd)
    elif cmd == CMD.MAX_FORWARD:
        print(cmd)
    elif cmd == CMD.MAX_BACKWARD:
        print(cmd)
    elif cmd == CMD.MAX_TURN_LEFT:
        print(cmd)
    elif cmd == CMD.MAX_TURN_RIGHT:
        print(cmd)
