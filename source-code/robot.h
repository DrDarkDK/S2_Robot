#ifndef ROBOT_H
#define ROBOT_H

#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <iostream>
#include <vector>
#include <string> 
#include "assert.h"
#include "database.h"
#include "SerialPort.h"

//NOTE: chessPos to roboPos

class Position {
public:
    //Position(int posX=0, int posY=0, int posZ=0);


    //Get the coordinates all inside a vector: {x, y, z};
    std::vector<int> getCoordinates();
private:
    int _x;
    int _y;
    int _z;
};

class Gripper {
public:
    Gripper() {};

    //Open or close the gripper.
    void open();
    void close();
private:
    bool _isOpen;
};


//Software <-> Robot, code is handled in 'functionality.cpp'.
class Robot { //Singleton type. Access anywhere through: Robot* robot = Robot::getInstance();
public:
    //Initalize the physical coordaintes of each square on the chessboard

    

    void initializeBoardCoordinates();

    std::vector<double> getBoardCoordinates(int col, int row);
    //Move a chess piece from on square to another
    void movePiece(const std::vector<double>& from, const std::vector<double>& to); //moves the piece from one square to another 



   
    ~Robot(); //Destructor 

    
    // Deleted copy constructor and assignment operator to prevent copying
    Robot(const Robot&) = delete;
    Robot& operator=(const Robot&) = delete;

    //Access point to the instance.
    static Robot* getInstance() {
        std::cout << "connecting to robot " << std::endl;
        if (instance == nullptr) {  // Create a new instance if one does not exist
            instance = new Robot("192.168.1.53");
            instance->initializeBoardCoordinates();
        }
        return instance;
    }
    //void movePiece(std::vector<int> fromPos, std::vector<int> toPos) {}; //Each position is an {x,y} coordinate set, with numbers from 1 to 8. so from 1x1 to 8x8. 

   
private:

    static Robot* instance; //Singleton instance of the Robot class
    ur_rtde::RTDEControlInterface rtde_control; //Control interface for sending commands to the robot
    ur_rtde::RTDEReceiveInterface rtde_receive; //Interface to receive data from the robot
    //std::vector<std::vector<std::vector<double>>> boardCoordinates; // 3D vector to store physical coordiantes of each chess square 
    std::vector<std::vector<std::vector<double>>> boardCoordinates;

    //Private constructor to enforce singleton pattern
    Robot(const std::string& ip);

    Robot();
    Gripper _gripper;
    Position _coordinates;
};

#endif //ROBOT_H