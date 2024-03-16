#include <iostream>
#include <vector>
#include "robotics.h"

void printArray(std::vector<std::vector<std::shared_ptr<ChessPiece>>>& array);
std::shared_ptr<ChessPiece> addChessPiece(ChessBoard& board, ChessPiece& piece, std::vector<int> position);

int main() {
    std::vector<std::shared_ptr<ChessPiece>> pieces;
    ChessBoard board;

    for (int i = 0; i < 8; i++) {
        ChessPiece pawnW("PAW", ChessPiece::WHITE); //Pawn
        pieces.push_back(addChessPiece(board, pawnW, {6, i}));

        ChessPiece pawnB("PAW", ChessPiece::BLACK); //Pawn
        pieces.push_back(addChessPiece(board, pawnB, {1, i}));
    }

    printArray(board.getGrid()); //Output the chessboard to the terminal.

    return 0;
}

std::shared_ptr<ChessPiece> addChessPiece(ChessBoard& board, ChessPiece& piece, std::vector<int> position) {
    if (!verifyPosition(position)) {
        std::cout << "Error! addChessPiece() expected coordinate lower than or equal to 8." << std::endl;
    }
    std::shared_ptr<ChessPiece> piecePtr = std::make_shared<ChessPiece>(std::move(piece));
    board.placePiece(piecePtr, position);
    return piecePtr;
}

//Debugging code: outputs the chessboard, if given "board.getGrid()" as a parameter.
void printArray(std::vector<std::vector<std::shared_ptr<ChessPiece>>>& array) {
    for (const auto& row : array) {
        for (const auto& elem : row) {
            if (elem != nullptr) {
                std::cout << elem->getType() << ' ';
            } else {
                std::cout << "|||" << ' ';
            }
        }
        std::cout << '\n';
    }
}
