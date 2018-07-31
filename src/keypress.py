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
    else:
        print("Invalid command key: {}".format(repr(key)))

    return True
