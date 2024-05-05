#include "robot.h"
#include <iostream> 

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

//Initialize static singleton instance to nullptr
Robot* Robot::instance = nullptr; 

//Constructor sets up RTDE control and receive interfaces 
Robot::Robot(const std::string& ip) : rtde_control(ip), rtde_receive(ip) {
    //The constructor remains empty for setting corners later 
}

//Singleton access method. Creates an instance if none exists and returns the existing instance. 
Robot* Robot::getInstance(){
    if(instance == nullptr){
        instance = new Robot("127.0.0.1"); //IP address of the UR robot
    }
    return instance; 
}


void Robot::initializeBoardCoordinates(const std::vector<double>& topLeft, 
                                       const std::vector<double>& topRight,
                                       const std::vector<double>& bottomLeft, 
                                       const std::vector<double>& bottomRight) {
    boardCoordinates.resize(8, std::vector<std::vector<double>>(8, std::vector<double>(3)));
    std::vector<std::vector<double>> topEdge(8), bottomEdge(8);

    // Interpolating top and bottom edges
    for (int i = 0; i < 8; ++i) {
        double t = i / 7.0;
        topEdge[i].resize(3);
        bottomEdge[i].resize(3);
        for (int j = 0; j < 3; ++j) {
            topEdge[i][j] = topLeft[j] + t * (topRight[j] - topLeft[j]);
            bottomEdge[i][j] = bottomLeft[j] + t * (bottomRight[j] - bottomLeft[j]);
        }
    }

    // Interpolating between top and bottom edges for each square
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            double t = j / 7.0;
            boardCoordinates[i][j].resize(3);
            for (int k = 0; k < 3; ++k) {
                boardCoordinates[i][j][k] = topEdge[i][k] + t * (bottomEdge[i][k] - topEdge[i][k]);
            }
        }
    }
}

// Moves a chess piece from one square to another using robot commands
void Robot::movePiece(const std::vector<int>& from, const std::vector<int>& to) {
    std::vector<double> startPos = boardCoordinates[from[0]][from[1]];
    std::vector<double> endPos = boardCoordinates[to[0]][to[1]];

    // Commands for robot to execute the move
    rtde_control.moveL({startPos[0], startPos[1], startPos[2] + 0.15}, 0.25, 0.5); // Lift the piece
    rtde_control.moveL({endPos[0], endPos[1], startPos[2]}, 0.25, 0.5); // Move to new position and lower the piece
}

// Destructor to ensure clean up
Robot::~Robot() {
    rtde_control.stopScript(); // Stop the robot's control script
}
/*Robot::Robot() : _gripper(Gripper()), _coordinates(Position()) {
    // Initialize your Robot's components and state here
}*/



int main() {
    // Define the physical coordinates of the chessboard corners
    std::vector<double> topLeft = {0.0, 0.0, 0.0};      // Physical coordinate of the top-left corner
    std::vector<double> topRight = {0.8, 0.0, 0.0};     // Physical coordinate of the top-right corner
    std::vector<double> bottomLeft = {0.0, 0.8, 0.0};   // Physical coordinate of the bottom-left corner
    std::vector<double> bottomRight = {0.8, 0.8, 0.0};  // Physical coordinate of the bottom-right corner

    // Get the singleton instance of the robot
    Robot* robot = Robot::getInstance();

    // Initialize board coordinates with the given corners
    robot->initializeBoardCoordinates(topLeft, topRight, bottomLeft, bottomRight);

    // Coordinates for moving a piece from E2 to E4 (considering the board 0-indexed and bottom-left origin)
    std::vector<int> startPos = {4, 1}; // E2
    std::vector<int> endPos = {4, 3};   // E4

    // Move the piece
    robot->movePiece(startPos, endPos);
    
    return 0;
}


