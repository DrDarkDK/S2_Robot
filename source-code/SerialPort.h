#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

//C++ <-> Microcontroller, communication.
class SerialPort {
public:
    SerialPort(const char* device, speed_t baudRate);

    //Send a message to the microcontroller.
    void writeSerial(const char* buf, size_t size);
    
    //Check if the connection is open.
    bool isOpen() const;

    ~SerialPort() {
        if (serial_fd != -1) {
            close(serial_fd);
        }
    }
private:
    int serial_fd;
};

#endif