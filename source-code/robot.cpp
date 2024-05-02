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
Robot::Robot() : _gripper(Gripper()), _coordinates(Position()) {
    // Initialize your Robot's components and state here
}

Robot* Robot::instance = nullptr;