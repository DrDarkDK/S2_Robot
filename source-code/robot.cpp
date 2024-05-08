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


//Initialize static singleton instance to nullptr
Robot* Robot::instance = nullptr; 

//Constructor sets up RTDE control and receive interfaces 
Robot::Robot(const std::string& ip) : rtde_control(ip), rtde_receive(ip) {
    //The constructor remains empty for setting corners later 
}

std::vector<double> Robot::getBoardCoordinates(const std::vector<int>& boardPos) {
    assert(boardPos[0] < 8 && boardPos[1] < 8 && boardPos[0] >= 0 && boardPos[1] >= 0);
        return boardCoordinates[boardPos[1]][boardPos[0]]; // Note the index order might need adjusting based on your coordinate setup
     
}



void Robot::initializeBoardCoordinates() {
    
    std::vector<double> topLeft = {0.0, 0.0, 0.0};
    std::vector<double> topRight = {0.8, 0.0, 0.0};
    std::vector<double> bottomLeft = {0.0, 0.8, 0.0};
    std::vector<double> bottomRight = {0.8, 0.8, 0.0};
    
    
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
void Robot::movePiece(const std::vector<double>& from, const std::vector<double>& to) {
    std::vector<double> startPos = boardCoordinates[from[0]][from[1]];
    std::vector<double> endPos = boardCoordinates[to[0]][to[1]];

    // Commands for robot to execute the move


   /* double velocity = 0.5;
    double acceleration = 0.5;
    std::vector<double> start = {startPos[0], startPos[1], startPos[2], 0, 0, 0, velocity};
    std::vector<double> end = {endPos[0], endPos[1], endPos[2], 0, 0, 0, velocity};
    
    std::cout << "about to move piece" << std::endl;
    rtde_control.moveL(start); // Lift the piece
    rtde_control.moveL(end); // Move to new position and lower the piece
    /*rtde_control.moveL({startPos[0], startPos[1], startPos[2] + 0.15}, 0.25, 0.5); // Lift the piece
    rtde_control.moveL({endPos[0], endPos[1], startPos[2]}, 0.25, 0.5); // Move to new position and lower the piece*/
    


    double velocity = 0.5;
    double acceleration = 0.5;
    double blend_1 = 0.0;
    double blend_2 = 0.02;
    double blend_3 = 0.0;
    std::vector<double> path_pose1 = {-0.143, -0.435, 0.20, -0.001, 3.12, 0.04, velocity, acceleration, blend_1};
    std::vector<double> path_pose2 = {-0.143, -0.51, 0.21, -0.001, 3.12, 0.04, velocity, acceleration, blend_2};
    std::vector<double> path_pose3 = {-0.32, -0.61, 0.31, -0.001, 3.12, 0.04, velocity, acceleration, blend_3};

    std::vector<std::vector<double>> path;
    path.push_back(path_pose1);
    path.push_back(path_pose2);
    path.push_back(path_pose3);

    //Save position to database.
    DatabaseManager DB;
    DB.connect();
    DB.savePosition({path_pose1[0], path_pose1[1], path_pose1[2]});
    DB.disconnect();

    // Send a linear path with blending in between - (currently uses separate script)
    rtde_control.moveL(path);
}

// Destructor to ensure clean up
Robot::~Robot() {
    rtde_control.stopScript(); // Stop the robot's control script
}
/*Robot::Robot() : _gripper(Gripper()), _coordinates(Position()) {
    // Initialize your Robot's components and state here
}*/

