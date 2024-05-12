#include "robot.h"


// --POSITION--

//Position::Position(int posX, int posY, int posZ) : _x(posX), _y(posY), _z(posZ) {}

/*std::vector<int> Position::getCoordinates() {
    return {_x, _y, _z};
}*/


// -- GRIPPER --
void Gripper::open() {
    SerialPort sp("/dev/ttyUSB0", B9600);
    if (sp.isOpen()) {
        sp.writeSerial("OPEN\n", 6);
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


//Initialize static singleton instance to nullptr
Robot* Robot::instance = nullptr; 

//Constructor sets up RTDE control and receive interfaces 
Robot::Robot(const std::string& ip) : rtde_control(ip), rtde_receive(ip) {
    //The constructor remains empty for setting corners later 
}

/*std::vector<double> Robot::getBoardCoordinates(const std::vector<int>& boardPos) {
    assert(boardPos[0] < 8 && boardPos[1] < 8 && boardPos[0] >= 0 && boardPos[1] >= 0);
        return boardCoordinates[boardPos[1]][boardPos[0]]; // Note the index order might need adjusting based on your coordinate setup
     
}*/





/*void Robot::initializeBoardCoordinates() {
    // Define the corner coordinates
    std::vector<double> bottomLeft = {0.2865, -0.228}; // starting point
    std::vector<double> bottomRight = {-0.072, -0.387}; // more negative x
    std::vector<double> topLeft = {0.4443, -0.595}; // more negative y
    std::vector<double> topRight ={0.071, -0.754};


    //Top left {0.365. -0.5, 0.19}
    //Top right {0.146, -0.589, 0.19}
    //Bottom left {0.282, -0.272, 0.19}
    //Bottom right {0.055, -0.3645, 0.19}
    //Center {0.2185, -0.425, 0.19}

    // Resize the board coordinates to hold 8x8 grid
    boardCoordinates.resize(8, std::vector<std::vector<double>>(8));

    // Calculate the width (x-direction) and height (y-direction) of each square
    double width = (bottomRight[0] - bottomLeft[0]) / 8.0; // Negative value, decreasing x
    double height = (topLeft[1] - bottomLeft[1]) / 8.0; // Negative value, decreasing y

    for (int col = 0; col < 8; ++col) {
        for (int row = 0; row < 8; ++row) {
            // Calculate the center coordinates for each square
            // x should become more negative as we move right (negative width)
            // y should also become more negative as we move up (negative height)
            double x = topLeft[0] + (col * width) + (width / 2.0);
            double y = topLeft[1] - (row * height) - (height / 2.0);

            boardCoordinates[row][col] = {x, y};
        }
    }
}*/



void Robot::initializeBoardCoordinates() {
    // Define the corner coordinates
    std::vector<double> bottomLeft = {0.2, -0.35};
    std::vector<double> bottomRight = {-0.2, -0.335};
    std::vector<double> topLeft = {0.2, -0.75};
    std::vector<double> topRight ={0.071, -0.754};

    // Resize the board coordinates to hold 8x8 grid
    boardCoordinates.resize(8, std::vector<std::vector<double>>(8));

    // Calculate the width and height of each square
    double width = (bottomRight[0] - bottomLeft[0]) / 8.0;
    double height = (topLeft[1] - bottomLeft[1]) / 8.0;

    // Angle in radians
    double angle = 24.92 * M_PI / 180.0; // Convert degrees to radians
    double cosTheta = cos(angle);
    double sinTheta = sin(angle);

    for (int col = 0; col < 8; ++col) {
        for (int row = 0; row < 8; ++row) {
            double x = bottomLeft[0] + (col * width) + (width / 2.0);
            double y = bottomLeft[1] + (row * height) + (height / 2.0);

            // Apply the rotation matrix
            double rotatedX = x * cosTheta - y * sinTheta;
            double rotatedY = x * sinTheta + y * cosTheta;

            boardCoordinates[row][col] = {rotatedX, rotatedY};
        }
    }
}

//Top-RIght {0.-217, -0.724}


/*std::vector<double> getBoardCoordinates(int col, int row){
    assert(col >= 0 & col < 8 && row >= 0 && row <8);
    return boardCoordinates[col][row];
}*/

std::vector<double> Robot::getBoardCoordinates(int col, int row) {
    assert(col >= 0 && col < 8 && row >= 0 && row < 8);  // Validate indices
    return boardCoordinates[col][row];  // Return x and y coordinates
}


// Moves a chess piece from one square to another using robot commands
void Robot::movePiece(const std::vector<double>& from, const std::vector<double>& to) {
    //std::vector<double> startPos = boardCoordinates[from[0]][from[1]];
    //std::vector<double> endPos = boardCoordinates[to[0]][to[1]];

    std::cout << "start pos found "<< std::endl; 
    std::cout <<  "x" << from[0] << ",  y" << from[1] << std::endl; 
    std::vector<double> startPos = getBoardCoordinates(from[0], 7-from[1]);
    std::cout << "end pos found" << std::endl;
    std::cout <<  "x" << to[0] << ",  y" << to[1] << std::endl; 
    std::vector<double> endPos = getBoardCoordinates(to[0], 7-to[1]);
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
    
    
    

    double velocity = 0.02;
    double acceleration = 0.02;
    double blend_1 = 0.0;
    std::vector<double> path_pose1 = {from[0], from[1], 0.21, -0.001, 3.12, 0.04, velocity, acceleration, blend_1};
    std::vector<double> path_pose2 = {to[0], to[1], 0.21, -0.001, 3.12, 0.04, velocity, acceleration, blend_1};
  

    std::vector<std::vector<double>> path;
    path = {};
    path.push_back(path_pose1);
    path.push_back(path_pose2);

    //Save position to database.
    DatabaseManager DB;
    DB.connect();
    DB.savePosition({path_pose1[0], path_pose1[1]});
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

