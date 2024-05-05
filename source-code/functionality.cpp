#include <iostream>
#include <memory>
#include "functionality.h"
#include "visuals.h"
#include "robot.h"

// --- CHESSPIECE CLASS ---


// Constructor implementation
ChessPiece::ChessPiece(std::string type, Color color, sf::Texture& texture) : _type(type), _color(color), _texture(texture), _position(2, -1) {

}

// displayInfo() implementation
void ChessPiece::displayInfo() const {
    std::cout << "Chess Piece: " << _type << ", Color: ";
    std::cout << (_color == WHITE ? "White" : "Black");
    std::cout << ", Position: (" << _position[0] << ", " << _position[1] << ")" << std::endl;
}

std::string ChessPiece::getType() const {
    return _type;
}

std::vector<int> ChessPiece::getPosition() const {
    return _position;
}

sf::Texture& ChessPiece::getTexture() const {
    return _texture;
}

void ChessPiece::setTexture(sf::Texture& texture) {
    _texture = texture;
}

void ChessPiece::setPosition(std::vector<int> position) {
    _position = position;
}


// --- CHESSBOARD CLASS ---


std::shared_ptr<ChessPiece> ChessBoard::getPosition(std::vector<int> position) {
    if (!verifyPosition(position)) {
        return NULL;
    }
    return grid[position[1]][position[0]];
}

void ChessBoard::placePiece(const std::shared_ptr<ChessPiece>& chessPiece, std::vector<int> position) {
    if (!verifyPosition(position)) {
        return;
    }
    if (verifyPosition(chessPiece->getPosition())) { //If the chesspiece exists already...
        this->wipePosition(chessPiece->getPosition()); //Wipe old position.
    }
    
    this->grid[position[0]][position[1]] = chessPiece; //Move the piece to new position.
    chessPiece->setPosition(position);

    this->pieces.push_back(chessPiece);
}

/*void ChessBoard::movePiece(std::vector<int> fromPos, std::vector<int> toPos) {
    Robot* robot = Robot::getInstance();
    std::shared_ptr<ChessPiece> obj_toPiece = this->getPosition({toPos[1], toPos[0]});
    
    

    if (this->getPosition({toPos[1], toPos[0]}) != nullptr) {
        std::cout << "Overlap!" << std::endl;

        for (int i = 0; i < this->getPieces().size(); i++) {
            //std::cout << this->getPieces()[i]->getType() << std::endl;
            if (this->getPieces()[i]->getPosition()[0] == toPos[0] && this->getPieces()[i]->getPosition()[1] == toPos[1]) {
                //std::cout << "Found Found! (" << i << ") | " << this->getPieces()[i]->getType() << std::endl;
                //std::cout << "(" << this->getPieces()[i]->getPosition()[0] << ", " << this->getPieces()[i]->getPosition()[1] << ")" << std::endl;
                std::cout << "Attempting to delete (" << toPos[0] << ", " << toPos[0] << ") | " << this->getPieces()[i]->getType() << std::endl;;
                delPiece(i);
            }
        }
    }

    if (this->getPosition(fromPos) != nullptr) { //Check if nullptr.
        this->placePiece(this->getPosition(fromPos), toPos);
        robot->movePiece(fromPos, toPos);
    } else {
        if (this->getPosition({fromPos[1], fromPos[0]}) != nullptr) { //Workaround. Some coordinates got inverted somewhere in the code.
            this->placePiece(this->getPosition({fromPos[1], fromPos[0]}), toPos);
        } else {
            std::cout << "Error! movePiece expected specificed pointer, and recieved a nullptr." << std::endl;
        }
    }
}*/

void ChessBoard::movePiece(std::vector<int> fromPos, std::vector<int> toPos) {
    Robot* robot = Robot::getInstance();
    std::shared_ptr<ChessPiece> toPiece = this->getPosition({toPos[1], toPos[0]});

    // Check if the destination position already has a piece
    if (toPiece != nullptr) {
        std::cout << "Overlap! Removing piece from position: " << toPos[0] << ", " << toPos[1] << std::endl;

        // Iterate through all pieces to find and remove the overlapping piece
        for (auto it = this->pieces.begin(); it != this->pieces.end(); ++it) {
            if ((*it)->getPosition()[0] == toPos[0] && (*it)->getPosition()[1] == toPos[1]) {
                pieces.erase(it);
                break; // Exit loop after deleting the piece to avoid iterator invalidation issues
            }
        }
    }

    // Ensure fromPos and toPos are mapped correctly from game logic positions to robot coordinate positions
    std::vector<double> startPos = robot->getBoardCoordinates(fromPos);
    std::vector<double> endPos = robot->getBoardCoordinates(toPos);

    // Command the robot to physically move the piece using the start and end positions
    robot->movePiece(startPos, endPos);
}

void ChessBoard::wipePosition(std::vector<int> position) {
    if (verifyPosition(position)) {
        this->grid[position[0]][position[1]] = nullptr;
    } else {
        std::cout << "Error! wipePosition() expected coordinate lower than or equal to 8." << std::endl;
    }
}

std::vector<std::shared_ptr<ChessPiece>> ChessBoard::getPieces() {
    return this->pieces;
}

void ChessBoard::delPiece(int pieceIndex) {
    pieces.erase(pieces.begin() + pieceIndex);
}