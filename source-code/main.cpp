#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp> 
#include <cxxabi.h>
#include <string>
#include <cctype>
#include "general.h"
#include "unitTests.h"
#include "functionality.h"
#include "visuals.h"

void initializeTextures();


int main() {
    UnitTest GlobalTest("Global Test (1)", true, 50, true); //UnitTest(name, performTests, µsTarget, debug)
    GlobalTest.startTests();

    initializeTextures(); 

    std::vector<std::shared_ptr<ChessPiece>> pieces; //Array containing all chess pieces.
    ChessBoard board; //The chessboard.

    for (int i = 0; i < 8; i++) { //Add pawns to the board.
        createPiece("Pawn", true, PieceTexture::whitePawn, {6, i}, board, pieces);
        //pieces.push_back(addChessPiece(board, pawnW, {6, i}));

        createPiece("Pawn", false, PieceTexture::blackPawn, {1, i}, board, pieces);
    }

    createPiece("Rook", false, PieceTexture::blackRook, {0, 0}, board, pieces);
    createPiece("Rook", false, PieceTexture::blackRook, {0, 7}, board, pieces);
    createPiece("Knights", false, PieceTexture::blackKnight, {0, 1}, board, pieces);
    createPiece("Knights", false, PieceTexture::blackKnight, {0, 6}, board, pieces);
    createPiece("Bishop", false, PieceTexture::blackBishop, {0, 2}, board, pieces);
    createPiece("Bishop", false, PieceTexture::blackBishop, {0, 5}, board, pieces);
    createPiece("Queen", false, PieceTexture::blackQueen, {0, 3}, board, pieces);
    createPiece("King", false, PieceTexture::blackKing, {0, 4}, board, pieces);


    createPiece("Rook", true, PieceTexture::whiteRook, {7, 0}, board, pieces);
    createPiece("Rook", true, PieceTexture::whiteRook, {7, 7}, board, pieces);
    createPiece("Knights", true, PieceTexture::whiteKnight, {7, 1}, board, pieces);
    createPiece("Knights", true, PieceTexture::whiteKnight, {7, 6}, board, pieces);
    createPiece("Bishop", true, PieceTexture::whiteBishop, {7, 2}, board, pieces);
    createPiece("Bishop", true, PieceTexture::whiteBishop, {7, 5}, board, pieces);
    createPiece("Queen", false, PieceTexture::whiteQueen, {7, 3}, board, pieces);
    createPiece("King", true, PieceTexture::whiteKing, {7, 4}, board, pieces);

    //board.movePiece({0,7}, {3,7});

    


    printGrid(board.getGrid()); //Output the chessboard to the terminal.

    GlobalTest.finalizeTests(); //ALL non-visual code should be above this line, to have the loading-time included in the test.

    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess Board");

    int squareSize = window.getSize().x / 8;
    std::vector<sf::Sprite> pieceSprites;
    initializePieces(pieceSprites, squareSize, pieces);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        

        window.clear();

        sf::Color col1(238, 208, 159);
        sf::Color col2(181, 136, 99);
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
                square.setPosition(j * squareSize, i * squareSize);
                square.setFillColor((i + j) % 2 == 0 ? col1 : col2);
                window.draw(square);
            }
        }

        for (const sf::Sprite& sprite : pieceSprites) {
            window.draw(sprite);
        }

        window.display();
    }

    return 0;
}