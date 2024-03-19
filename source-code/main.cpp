#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp> 
#include <cxxabi.h>
#include "general.h"
#include "unitTests.h"
#include "functionality.h"
#include "visuals.h"


void initializeTextures();

int main() {
    performTests(true);
    initializeTextures();

    //André
    std::vector<std::shared_ptr<ChessPiece>> pieces; //Array containing all chess pieces.
    ChessBoard board; //The chessboard.

    for (int i = 0; i < 8; i++) { //Add pawns to the board.
        ChessPiece pawnW("PAW", ChessPiece::WHITE); //Pawn
        //pieces.push_back(addChessPiece(board, pawnW, {6, i}, PieceTexture::whitePawn));

        ChessPiece pawnB("PAW", ChessPiece::BLACK); //Pawn
        pieces.push_back(addChessPiece(board, pawnB, {1, i}, PieceTexture::blackPawn));
    }

    //printGrid(board.getGrid()); //Output the chessboard to the terminal.

    //Casper
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