#include <iostream>
#include <memory>
#include "robotics.h"

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

void ChessPiece::setPosition(std::vector<int> position) {
    _position = position;
}


// --- CHESSBOARD CLASS ---


std::shared_ptr<ChessPiece> ChessBoard::getPosition(std::vector<int> position) {
    if (!verifyPosition(position)) {
        std::cout << "Error! getPosition() expected coordinate lower than or equal to 8.";
    }
    return grid[position[0]][position[1]];
}

void ChessBoard::placePiece(const std::shared_ptr<ChessPiece>& chessPiece, std::vector<int> position) {
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


// --- PIECETEXTURE CLASS ---


//Sends back erro if the sprite for the piece can't be found
sf::Texture PieceTexture::loadTexture(std::string str){
    sf::Texture tmp;
    if (!tmp.loadFromFile(str))
        std::cout << "Could not find sprite\n";
    return tmp;
}

//Initialize black pieces 
sf::Texture PieceTexture::blackKing = PieceTexture::loadTexture("Assets/b_king.png");
sf::Texture PieceTexture::blackQueen = PieceTexture::loadTexture("Assets/b_queen.png");
sf::Texture PieceTexture::blackRook = PieceTexture::loadTexture("Assets/b_rook.png");
sf::Texture PieceTexture::blackKnight = PieceTexture::loadTexture("Assets/b_knight.png");
sf::Texture PieceTexture::blackBishop = PieceTexture::loadTexture("Assets/b_bishop.png");
sf::Texture PieceTexture::blackPawn = PieceTexture::loadTexture("Assets/b_pawn.png");

//Initialize white pieces

sf::Texture PieceTexture::whiteKing = PieceTexture::loadTexture("Assets/w_king.png");
sf::Texture PieceTexture::whiteQueen = PieceTexture::loadTexture("Assets/w_queen.png");
sf::Texture PieceTexture::whiteRook = PieceTexture::loadTexture("Assets/w_rook.png");
sf::Texture PieceTexture::whiteKnight = PieceTexture::loadTexture("Assets/w_knight.png");
sf::Texture PieceTexture::whiteBishop = PieceTexture::loadTexture("Assets/w_bishop.png");
sf::Texture PieceTexture::whitePawn = PieceTexture::loadTexture("Assets/w_pawn.png");

