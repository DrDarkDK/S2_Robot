#include "SerialPort.h"

SerialPort::SerialPort(const char* device, speed_t baudRate) {
    serial_fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_fd == -1) {
        std::cerr << "Failed to open serial port" << std::endl;
        return;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(serial_fd, &tty) != 0) {
        std::cerr << "Failed to get serial attributes" << std::endl;
        close(serial_fd);
        return;
    }

    cfsetospeed(&tty, baudRate);
    cfsetispeed(&tty, baudRate);

    tty.c_cflag &= ~(PARENB | CSTOPB | CSIZE | CRTSCTS);
    tty.c_cflag |= CS8 | CREAD | CLOCAL;
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY | IGNBRK | BRKINT | INPCK | ISTRIP | ICRNL);
    tty.c_oflag &= ~OPOST;

    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
        std::cerr << "Error from tcsetattr" << std::endl;
        close(serial_fd);
    }
}

void SerialPort::writeSerial(const char* buf, size_t size) {
    if (write(serial_fd, buf, size) == -1) {
        std::cerr << "Failed to write to serial port" << std::endl;
    }
}

bool SerialPort::isOpen() const {
        return serial_fd != -1;
    }