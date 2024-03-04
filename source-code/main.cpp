#include <iostream>
#include "robotics.h"

int main() {
    ChessPiece pawn("Pawn", ChessPiece::WHITE);
    ChessPiece knight("Knight", ChessPiece::BLACK);

    pawn.displayInfo();
    knight.displayInfo();

    return 0;
}