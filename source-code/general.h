#ifndef GENERAL_H
#define GENERAL_H

#include <cxxabi.h>
#include "functionality.h"
#include "visuals.h"

//Will handle the creation of a new chesspiece and add it to the "pieces" array.
void createPiece(std::string type, bool isWhite, sf::Texture& texture, std::vector<int> position, ChessBoard& board, std::vector<std::shared_ptr<ChessPiece>>& pieces);

std::vector<float> coordsToPosition(std::vector<float> position);

//Add a chess piece (object) to a chessboard.
std::shared_ptr<ChessPiece> addChessPiece(ChessBoard& board, ChessPiece& piece, std::vector<int> position);

// Template function to get the type name of any variable as a string
template<typename T>
std::string getTypeName(const T& var) {
    
        int status = -1; 
        std::unique_ptr<char, void(*)(void*)> res {
            abi::__cxa_demangle(typeid(var).name(), NULL, NULL, &status),
            std::free
        };
        std::string result = (status==0) ? res.get() : typeid(var).name() ;

    return result;
}

//Debugging code: outputs the chessboard, if given "board.getGrid()" as a parameter.
void printGrid(const std::vector<std::vector<std::shared_ptr<ChessPiece>>>& array);


// Helper function to calculate the scaling factor for the sprites
float calculateScaleFactor(const sf::Texture& texture, int squareSize);

// Function to initialize chess piece sprites and their positions
void initializePieces(std::vector<sf::Sprite>& sprites, int squareSize, std::vector<std::shared_ptr<ChessPiece>>& pieces);

#endif