#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/select.h>
#include <string>

class SerialPort {
    int serial_fd;

public:
    SerialPort(const char* device, speed_t baudRate) {
        serial_fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
        if (serial_fd == -1) {
            perror("Failed to open serial port");
            return;
        }

        struct termios tty;
        memset(&tty, 0, sizeof(tty));
        if (tcgetattr(serial_fd, &tty) != 0) {
            perror("Failed to get serial attributes");
            close(serial_fd);
            serial_fd = -1;
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
            perror("Error from tcsetattr");
            close(serial_fd);
            serial_fd = -1;
            return;
        }
    }

    ~SerialPort() {
        if (serial_fd != -1) {
            close(serial_fd);
        }
    }

    ssize_t readSerial(char* buffer, size_t size) {
        return read(serial_fd, buffer, size);
    }

    bool isOpen() const {
        return serial_fd != -1;
    }

    int getSerialFD() const {
        return serial_fd;
    }
};

void setStdinEcho(bool enable = true) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable)
        tty.c_lflag &= ~ICANON;
    else
        tty.c_lflag |= ICANON;

    (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

int main() {
    SerialPort sp("/dev/ttyUSB0", B9600);
    setStdinEcho(false);

    if (sp.isOpen()) {
        std::string buffer;
        char temp_buf[256];

        std::cout << "Reading from serial port. Press any key to exit." << std::endl;

        fd_set read_fds;
        struct timeval tv;
        int retval;

        while (true) {
            FD_ZERO(&read_fds);
            FD_SET(STDIN_FILENO, &read_fds);
            FD_SET(sp.getSerialFD(), &read_fds);

            tv.tv_sec = 0;
            tv.tv_usec = 100000;

            int max_fd = std::max(STDIN_FILENO, sp.getSerialFD()) + 1;
            retval = select(max_fd, &read_fds, NULL, NULL, &tv);

            if (retval == -1) {
                perror("select()");
                break;
            } else if (retval) {
                if (FD_ISSET(STDIN_FILENO, &read_fds)) {
                    std::cout << "Key pressed, stopping program." << std::endl;
                    break;
                }

                if (FD_ISSET(sp.getSerialFD(), &read_fds)) {
                    ssize_t num_bytes = sp.readSerial(temp_buf, sizeof(temp_buf) - 1);
                    if (num_bytes > 0) {
                        temp_buf[num_bytes] = '\0';
                        buffer += temp_buf;

                        // Processing
                        size_t pos;
                        while ((pos = buffer.find('\n')) != std::string::npos) {
                            std::string message = buffer.substr(0, pos);
                            if (!message.empty() && message[0] != '\r') { // Ignore empty lines or lines with only carriage return
                                std::cout << "Received: " << message << std::endl;
                            }
                            buffer.erase(0, pos + 1);
                        }
                    }
                }
            }
        }
    }

    setStdinEcho(true);
    return 0;
}
