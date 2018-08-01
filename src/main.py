from input import input_read

from communication import init_serial

def main():
    print("Knight rider initialized")

    init_serial()
    input_read()


if __name__ == '__main__':
    main()
