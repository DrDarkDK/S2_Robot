#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <vector>

class Position {
public:
    Position(int posX, int posY, int posZ);

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


class Robot {
public:
    Robot(Position startPosition, Gripper robotGripper);

private:
    Gripper _gripper;
    Position _coordinates;
};

#endif