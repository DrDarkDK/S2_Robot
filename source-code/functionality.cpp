#include <iostream>
#include <memory>
#include "functionality.h"
#include "visuals.h"

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

void ChessBoard::movePiece(std::vector<int> fromPos, std::vector<int> toPos) {
    if (this->getPosition(fromPos) != nullptr) { //Check if nullptr.
        this->placePiece(this->getPosition(fromPos), toPos);
    } else {
        if (this->getPosition({fromPos[1], fromPos[0]}) != nullptr) { //Workaround. Some coordinates got inverted somewhere in the code.
            this->placePiece(this->getPosition({fromPos[1], fromPos[0]}), toPos);
        } else {
            std::cout << "Error! movePiece expected specificed pointer, and recieved a nullptr." << std::endl;
        }
    }
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