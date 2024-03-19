#include <iostream>
#include <memory>
#include "functionality.h"
#include "visuals.h"

bool verifyPosition(std::vector<int> position) {
    if (position[0] < 8 && position[1] < 8) {
        if (position[0] >= 0 && position[1] >= 0) {
            return true;
        }
    }
    return false;
}


// --- CHESSPIECE CLASS ---



// Constructor implementation
ChessPiece::ChessPiece(std::string type, Color color) : _type(type), _color(color), _position(2, -1) {

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

sf::Texture ChessPiece::getTexture() const {
    return _texture;
}

void ChessPiece::setTexture(sf::Texture texture) {
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
    return grid[position[0]][position[1]];
}

void ChessBoard::placePiece(const std::shared_ptr<ChessPiece>& chessPiece, std::vector<int> position) {
    if (!verifyPosition(position)) {
        return;
    }

    if (verifyPosition(chessPiece->getPosition())) {
        this->wipePosition(chessPiece->getPosition()); //Wipe old position.
    }
    
    this->grid[position[0]][position[1]] = chessPiece; //Move the piece to new position.
    chessPiece->setPosition(position);
}

void ChessBoard::movePiece(std::vector<int> fromPos, std::vector<int> toPos) {
    if (this->getPosition(fromPos) != nullptr) { //Check if nullptr.
        this->placePiece(this->getPosition(fromPos), toPos);
    } else {
        std::cout << "Error! movePiece expected specificed pointer, and recieved a nullptr.";
    }
}

void ChessBoard::wipePosition(std::vector<int> position) {
    if (verifyPosition(position)) {
        this->grid[position[0]][position[1]] = nullptr;
    } else {
        std::cout << "Error! wipePosition() expected coordinate lower than or equal to 8.";
    }
}