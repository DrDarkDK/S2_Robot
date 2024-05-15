#include "robot.h"
#include "SerialPort.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

// -- GRIPPER --
void Gripper::open() {
    SerialPort sp("/dev/ttyUSB0", B9600);
    if (sp.isOpen()) {
        sp.writeSerial("OPEN\n", 5);
        usleep(1000000);  // Wait for transmission to complete
    }
}

void Gripper::close() {
    SerialPort sp("/dev/ttyUSB0", B9600);
    if (sp.isOpen()) {
        sp.writeSerial("CLOSE\n", 6);
        usleep(1000000);  // Wait for transmission to complete
    }
}

// -- ROBOT --

Robot* Robot::instance = nullptr; 

Robot::Robot(const std::string& ip) : rtde_control(ip), rtde_receive(ip) {
    // Empty constructor
}

void Robot::initializeBoardCoordinates() {
    // Define the corner coordinates
    std::vector<double> bottomLeft = {0.2, -0.35};
    std::vector<double> bottomRight = {-0.2, -0.35};
    std::vector<double> topLeft = {0.2, -0.75};
    std::vector<double> topRight ={0.071, -0.754};

    boardCoordinates.resize(8, std::vector<std::vector<double>>(8));

    double width = (bottomRight[0] - bottomLeft[0]) / 8.0;
    double height = (topLeft[1] - bottomLeft[1]) / 8.0;

    double angle = 24.92 * M_PI / 180.0; // Convert degrees to radians
    double cosTheta = cos(angle);
    double sinTheta = sin(angle);

    for (int col = 0; col < 8; ++col) {
        for (int row = 0; row < 8; ++row) {
            double x = bottomLeft[0] + (col * width) + (width / 2.0);
            double y = bottomLeft[1] + (row * height) + (height / 2.0);

            double rotatedX = x * cosTheta - y * sinTheta;
            double rotatedY = x * sinTheta + y * cosTheta;

            boardCoordinates[row][col] = {rotatedX, rotatedY};
        }
    }
}

std::vector<double> Robot::getBoardCoordinates(int col, int row) {
    assert(col >= 0 && col < 8 && row >= 0 && row < 8);
    return boardCoordinates[col][row];
}

void Robot::movePiece(const std::vector<double>& from, const std::vector<double>& to) {
    std::cout << "start pos found " << std::endl; 
    std::cout <<  "x: " << from[0] << ", y: " << from[1] << std::endl; 
    std::vector<double> startPos = getBoardCoordinates(from[0], 7 - from[1]);
    std::cout << "end pos found" << std::endl;
    std::cout <<  "x: " << to[0] << ", y: " << to[1] << std::endl; 
    std::vector<double> endPos = getBoardCoordinates(to[0], 7 - to[1]);

    Gripper grip;
    //grip.close();
    grip.close();
    grip.open();

    double velocity = 0.02;
    double acceleration = 0.02;
    double blend = 0.0;

    std::vector<double> path_pose1 = {from[0], from[1], 0.25, -0.001, 3.12, 0.04, velocity, acceleration, blend};
    std::vector<double> path_pose2 = {from[0], from[1], 0.10, -0.001, 3.12, 0.04, velocity, acceleration, blend};
    std::vector<double> path_pose3 = {to[0], to[1], 0.25, -0.001, 3.12, 0.04, velocity, acceleration, blend};
    std::vector<double> path_pose4 = {to[0], to[1], 0.10, -0.001, 3.12, 0.04, velocity, acceleration, blend};

    std::vector<std::vector<double>> path = {path_pose1,  path_pose2, path_pose1, path_pose3, path_pose4, path_pose3};



    //rtde_control.moveL(path);
    //grip.close();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    //rtde_control.moveL(path_pose2);
    //grip.open();
}

Robot::~Robot() {
    rtde_control.stopScript();
}
