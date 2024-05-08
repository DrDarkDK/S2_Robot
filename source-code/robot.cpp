#include "robot.h"


// --POSITION--

//Position::Position(int posX, int posY, int posZ) : _x(posX), _y(posY), _z(posZ) {}

/*std::vector<int> Position::getCoordinates() {
    return {_x, _y, _z};
}*/


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

/*std::vector<double> Robot::getBoardCoordinates(const std::vector<int>& boardPos) {
    assert(boardPos[0] < 8 && boardPos[1] < 8 && boardPos[0] >= 0 && boardPos[1] >= 0);
        return boardCoordinates[boardPos[1]][boardPos[0]]; // Note the index order might need adjusting based on your coordinate setup
     
}*/





/*void Robot::initializeBoardCoordinates() {
    
    std::vector<double> topLeft = {0.365, -0.5, 0.19};
    std::vector<double> topRight = {0.146, -0.589, 0.19};
    std::vector<double> bottomLeft = {0.282, -0.272, 0.19};
    std::vector<double> bottomRight = {0.055, -0.3645, 0.19};
    std::vector<double> Center = {0.2185, -0.425, 0.19};
    

    //Top left {0.365. -0.5, 0.19}
    //Top right {0.146, -0.589, 0.19}
    //Bottom left {0.282, -0.272, 0.19}
    //Bottom right {0.055, -0.3645, 0.19}
    //Center {0.2185, -0.425, 0.19}

    std::vector<double> Top_Top = {0.219, 0.089, 0.19};
    std::vector<double> bot_bot = {0.227, 0.093, 0.19};
    std::vector<double> TopL_botL = {0.083, 0.228, 0.19};
    std::vector<double> TopR_botR = {0.091, 0.225, 0.19};

    for(int i = 0; i < 8; i++){


    }

    boardCoordinates.resize(8, std::vector<std::vector<double>>(8));

        // Calculate coordinates for each square, centering them
    for (int col = 0; col < 8; ++col) {
        double colRatio = (col + 0.5) / 8.0; // Adjusting to center the square

            // Interpolate top and bottom positions for this column
            std::vector<double> interpolatedTop(3), interpolatedBottom(3);
            for (int i = 0; i < 3; ++i) {
                interpolatedTop[i] = topLeft[i] + colRatio * (topRight[i] - topLeft[i]);
                interpolatedBottom[i] = bottomLeft[i] + colRatio * (bottomRight[i] - bottomLeft[i]);
            }

            // Set coordinates for each row in this column, centered
            for (int row = 0; row < 8; ++row) {
                double rowRatio = (row + 0.5) / 8.0; // Adjusting to center the square
                boardCoordinates[col][row].resize(3);
                for (int i = 0; i < 3; ++i) {
                    boardCoordinates[col][row][i] = interpolatedTop[i] + rowRatio * (interpolatedBottom[i] - interpolatedTop[i]);
                }
            }
    }
    

    
    /*boardCoordinates.resize(8, std::vector<std::vector<double>>(8, std::vector<double>(3)));
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
} */

/*void Robot::initializeBoardCoordinates() {
    std::vector<double> topLeft = {0.365, -0.5};
    std::vector<double> topRight = {0.146, -0.589};
    std::vector<double> bottomLeft = {0.282, -0.272};
    std::vector<double> bottomRight = {0.055, -0.3645};

    boardCoordinates.resize(8, std::vector<std::vector<double>>(8));

    for (int col = 0; col < 8; ++col) {
        double colRatio = (col + 0.5) / 8.0;

        std::vector<double> interpolatedTop(2), interpolatedBottom(2);
        for (int i = 0; i < 2; ++i) {
            interpolatedTop[i] = topLeft[i] + colRatio * (topRight[i] - topLeft[i]);
            interpolatedBottom[i] = bottomLeft[i] + colRatio * (bottomRight[i] - bottomLeft[i]);
        }

        for (int row = 0; row < 8; ++row) {
            double rowRatio = (row + 0.5) / 8.0;
            boardCoordinates[col][row].resize(2);
            for (int i = 0; i < 2; ++i) {
                boardCoordinates[col][row][i] = interpolatedTop[i] + rowRatio * (interpolatedBottom[i] - interpolatedTop[i]);
            }
        }
    }
}*/



void Robot::initializeBoardCoordinates() {
    // Define the corner coordinates
    std::vector<double> bottomLeft = {0.282, -0.272}; // starting point
    std::vector<double> bottomRight = {0.055, -0.3645}; // more negative x
    std::vector<double> topLeft = {0.365, -0.5}; // more negative y

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
            double x = bottomLeft[0] + (col * width) + (width / 2.0);
            double y = bottomLeft[1] + (row * height) + (height / 2.0);

            boardCoordinates[row][col] = {x, y};
        }
    }
}


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
    std::vector<double> startPos = getBoardCoordinates(from[0], from[1]);
    std::cout << "end pos found" << std::endl;
    std::cout <<  "x" << to[0] << ",  y" << to[1] << std::endl; 
    std::vector<double> endPos = getBoardCoordinates(to[0], to[1]);
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
    
    
    

    double velocity = 0.05;
    double acceleration = 0.05;
    double blend_1 = 0.0;
    std::vector<double> path_pose1 = {startPos[0], startPos[1], 0.21, -0.001, 3.12, 0.04, velocity, acceleration, blend_1};
    std::vector<double> path_pose2 = {endPos[0], endPos[1], 0.21, -0.001, 3.12, 0.04, velocity, acceleration, blend_1};
  

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

