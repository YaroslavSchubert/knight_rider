from commands import command, CMD

def keypress(key):
    """
    :return: False if you want to stop reading key presses
    """
    if key == 'q':
        return False
    elif key == ' ':
        command(CMD.STOP)
    elif key == 'up' or key == 'w':
        command(CMD.FORWARD)
    elif key == 'down' or key == 's':
        command(CMD.BACKWARD)
    elif key == 'left' or key == 'a':
        command(CMD.TURN_LEFT)
    elif key == 'right' or key == 'd':
        command(CMD.TURN_RIGHT)
    elif key == 'ctrl- ':
        command(CMD.MAX_STOP)
    elif key == 'ctrl-up' or key == 'ctrl-w':
        command(CMD.MAX_FORWARD)
    elif key == 'ctrl-down' or key == 'ctrl-s':
        command(CMD.MAX_BACKWARD)
    elif key == 'ctrl-left' or key == 'ctrl-a':
        command(CMD.MAX_TURN_LEFT)
    elif key == 'ctrl-right' or key == 'ctrl-d':
        command(CMD.MAX_TURN_RIGHT)
    elif key == '0':
        command(CMD.MOTORS_SELECT_ALL)
    elif key == '1':
        command(CMD.MOTORS_SELECT_1)
    elif key == '2':
        command(CMD.MOTORS_SELECT_2)
    elif key == '3':
        command(CMD.MOTORS_SELECT_3)
    elif key == '4':
        command(CMD.MOTORS_SELECT_4)
    elif key == '5':
        command(CMD.MOTORS_SELECT_5)
    elif key == '6':
        command(CMD.MOTORS_SELECT_6)
    elif key == 'u':
        command(CMD.SAVE_MAX)
    elif key == 'U':
        command(CMD.RESET_MAX)
    elif key == 'e':
        command(CMD.ENGINE_ON)
    elif key == 'E':
        command(CMD.ENGINE_OFF)
    else:
        print("Invalid command key: {}".format(repr(key)))

    return True
