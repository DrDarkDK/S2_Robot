#include "robot.h"


// --POSITION--

Position::Position(int posX, int posY, int posZ) : _x(posX), _y(posY), _z(posZ) {}

std::vector<int> Position::getCoordinates() {
    return {_x, _y, _z};
}


// -- GRIPPER --
void Gripper::open() {
    //TBA
}

void Gripper::close() {
    //TBA
}

// -- ROBOT --
Robot::Robot(Position startPosition, Gripper robotGripper) : _coordinates(startPosition), _gripper(robotGripper) {}