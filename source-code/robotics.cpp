#include <iostream>
#include "robotics.h"

// Constructor implementation
ChessPiece::ChessPiece(std::string type, Color color) : type(type), color(color) {}

// displayInfo() implementation
void ChessPiece::displayInfo() const {
    std::cout << "Chess Piece: " << type << ", Color: ";
    std::cout << (color == WHITE ? "White" : "Black") << std::endl;
}