#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <vector>

class Position {
public:
    Position(int posX=0, int posY=0, int posZ=0);

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
    // Deleted copy constructor and assignment operator to prevent copying
    Robot(const Robot&) = delete;
    Robot& operator=(const Robot&) = delete;

    //Access point to the instance.
    static Robot* getInstance() {
        if (instance == nullptr) {  // Create a new instance if one does not exist
            instance = new Robot();
        }
        return instance;
    }

    void movePiece(std::vector<int> fromPos, std::vector<int> toPos) {}; //Each position is an {x,y} coordinate set, with numbers from 1 to 8. so from 1x1 to 8x8. 

private:
    Robot();
    static Robot * instance;
    Gripper _gripper;
    Position _coordinates;
};

#endif