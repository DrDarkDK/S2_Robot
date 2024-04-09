#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp> 
//#include <cxxabi.h>
#include <string>
#include <cctype>
#include <thread>
#include "general.h"
#include "unitTests.h"
#include "functionality.h"
#include "visuals.h"

void initializeTextures();


int main() {
    UnitTest GlobalTest("Global Test", true, 50, true); //UnitTest(name, performTests, µsTarget, debug)
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

    GlobalTest.finalizeTests(); //ALL non-visual code should be above this line, to have the loading-time included in the test.

    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess Board");
    int squareSize = window.getSize().x / 8;

    auto lastTimeCheck = std::chrono::steady_clock::now();

    bool mouseHeld = false; //While the left mousebuttun is held down, this will be true.
    std::vector<int> clickTarget = {-1, -1}; //The position the cursor clicks "first".
    std::vector<int> releaseTarget = {-1, -1}; //The position the cursor clicks "last".

    while (window.isOpen()) {
          auto current_time = std::chrono::steady_clock::now();
           std::chrono::duration<double> elapsed = current_time - lastTimeCheck;

          std::vector<sf::Sprite> pieceSprites;
          initializePieces(pieceSprites, squareSize, pieces);

          //Check the window should be closed.
          sf::Event event;
          while (window.pollEvent(event)) {
              if (event.type == sf::Event::Closed) {
                  window.close();
              }
          }

          //When the left mousebutton is clicked.
          if (event.type == sf::Event::MouseButtonPressed && !mouseHeld) {
            if (event.mouseButton.button == sf::Mouse::Left) {
              mouseHeld = true;
              std::vector<int> cursorCoords = getCursorPosition(window);
              if (clickTarget[0] == -1) { //Find out where the user clicked, and if it's the first or second click.
                clickTarget = {cursorCoords[0], cursorCoords[1]};
              } else {
                releaseTarget = {cursorCoords[1], cursorCoords[0]};
              }
            }
          }
          if (mouseHeld && !(event.type == sf::Event::MouseButtonPressed)) { //Mouse released. Makes sure the above event is only run once per mouse being clicked.
            mouseHeld = false;
          }

        if (elapsed.count() >= 0.25) { //Slow down the unnecessary parts of the code, for optimization purposes.
          if (releaseTarget[0] >= 0) { //Check if a release position has been clicked.
            //Debugging code
            //std::cout << "Click Target: (" << clickTarget[0]+1 << ", " << clickTarget[1]+1 << ")" << std::endl;
            //std::cout << "Release Target: (" << releaseTarget[1]+1 << ", " << releaseTarget[0]+1 << ")" << std::endl;

            if (board.getPosition(releaseTarget) != nullptr) { //If a piece is already on the chosen position.
              board.wipePosition(releaseTarget);
            }

            if (board.getPosition(clickTarget) != nullptr && releaseTarget != clickTarget) { //Make sure the same place isn't clicked twice.
              board.movePiece(clickTarget, releaseTarget);
            }

            clickTarget = {-1, -1}; //Reset click target.
            releaseTarget = {-1, -1}; //Reset release target.
          }

          window.clear();

          //Predefined colors for chessboard cells.
          sf::Color primary_color(238, 208, 159); //White
          sf::Color secondary_color(181, 136, 99); //Black
          sf::Color clickTarget_color(116, 163, 111); //Green

          //Draw the chessboard using a nested (meaning 2D array in this case) for-loop.
          for (int i = 0; i < 8; ++i) {
              for (int j = 0; j < 8; ++j) {
                  sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
                  square.setPosition(j * squareSize, i * squareSize);
                  if (clickTarget[0] == j && clickTarget[1] == i) { //If the current position is equal to the "clickTarget" variable.
                    square.setFillColor(clickTarget_color);
                  } else {
                    square.setFillColor((i + j) % 2 == 0 ? primary_color : secondary_color); //Which between the primary and secondary color.
                  }
                  window.draw(square);
              }
          }

          for (const sf::Sprite& sprite : pieceSprites) {
              window.draw(sprite);
          }
          lastTimeCheck = current_time;

          window.display();
        }
    }

    return 0;
}