#include <iostream>
#include <memory>
#include "robotics.h"

/*
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

*/

// --- PIECETEXTURE CLASS ---

// Definitions of static textures
sf::Texture PieceTexture::blackKing;
sf::Texture PieceTexture::blackQueen;
sf::Texture PieceTexture::blackRook;
sf::Texture PieceTexture::blackKnight;
sf::Texture PieceTexture::blackBishop;
sf::Texture PieceTexture::blackPawn;

sf::Texture PieceTexture::whiteKing;
sf::Texture PieceTexture::whiteQueen;
sf::Texture PieceTexture::whiteRook;
sf::Texture PieceTexture::whiteKnight;
sf::Texture PieceTexture::whiteBishop;
sf::Texture PieceTexture::whitePawn;

sf::Texture PieceTexture::loadTexture(const std::string& path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Could not load texture from " << path << std::endl;
        exit(EXIT_FAILURE); // Exit if we cannot load the texture
    }
    return texture;
}

void initializeTextures() {
    PieceTexture::blackKing = PieceTexture::loadTexture("../Assets/b_king.png");
    PieceTexture::blackQueen = PieceTexture::loadTexture("../Assets/b_queen.png");
    PieceTexture::blackRook = PieceTexture::loadTexture("../Assets/b_rook.png");
    PieceTexture::blackKnight = PieceTexture::loadTexture("../Assets/b_knight.png");
    PieceTexture::blackBishop = PieceTexture::loadTexture("../Assets/b_bishop.png");
    PieceTexture::blackPawn = PieceTexture::loadTexture("../Assets/b_pawn.png");

    PieceTexture::whiteKing = PieceTexture::loadTexture("../Assets/w_king.png");
    PieceTexture::whiteQueen = PieceTexture::loadTexture("../Assets/w_queen.png");
    PieceTexture::whiteRook = PieceTexture::loadTexture("../Assets/w_rook.png");
    PieceTexture::whiteKnight = PieceTexture::loadTexture("../Assets/w_knight.png");
    PieceTexture::whiteBishop = PieceTexture::loadTexture("../Assets/w_bishop.png");
    PieceTexture::whitePawn = PieceTexture::loadTexture("../Assets/w_pawn.png");
}