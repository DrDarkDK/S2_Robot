#ifndef ROBOTICS_H
#define ROBOTICS_H

#include <string>

class ChessPiece {
public:
    // Enum for the color of the chess piece. Due to "enum" white will have the color 0, and black will have the color 1.
    enum Color {
        WHITE,
        BLACK
    };

    // Constructor
    ChessPiece(std::string type, Color color);

    // Method to display the chess piece's information
    void displayInfo() const;

private:
    std::string type; // Type of the chess piece, e.g., "Pawn", "Rook", etc.
    Color color;      // Color of the chess piece
};

#endif
