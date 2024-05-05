#include "robot.h"
#include <iostream>

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
