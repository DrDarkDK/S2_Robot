#ifndef ROBOTICS_H
#define ROBOTICS_H

#include <iostream> 
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include "visuals.h"

bool verifyPosition(std::vector<int> position);

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

        //Outputs which type of chess piece the object is.
        std::string getType() const;

        //Outputs the position of the chess piece, in an array with a length of 2. [row, column]
        std::vector<int> getPosition() const;

        sf::Texture getTexture() const;

        void setTexture(sf::Texture texture);

        //Sets the position of the pawn. This has no effect on the chessboard; only the piece!
        void setPosition(std::vector<int> position);

    private:
        std::string _type; // Type of the chess piece, e.g., "Pawn", "Rook", etc.
        Color _color;      // Color of the chess piece
        std::vector<int> _position; //Position in the chessboard.
        sf::Texture _texture;
};

class ChessBoard {
    public:
        //Constructor
        ChessBoard() {
            for (int i = 0; i < 8; ++i) {
                grid.emplace_back(8, nullptr);
            }
        };

        //Get the piece at a specific position.
        std::shared_ptr<ChessPiece> getPosition(std::vector<int> position);

        //Place a piece somewhere on the board grid.
        void placePiece(const std::shared_ptr<ChessPiece>& chessPiece, std::vector<int> position);
        
        //Move the piece at position "fromPos" to position "toPos".
        void movePiece(std::vector<int> fromPos, std::vector<int> toPos);

        //Wipe or empty the given position.
        void wipePosition(std::vector<int> position);

        //Return the nested array containing the grid.
        std::vector<std::vector<std::shared_ptr<ChessPiece>>> getGrid() {
            return grid;
        }

    private:
        std::vector<std::vector<std::shared_ptr<ChessPiece>>> grid; //A nested array containing the board grid.
};


#endif // ROBOTICS_H
