#include <iostream>
#include <vector>
#include <memory>
#include "robotics.h"
#include <SFML/Graphics.hpp> 

void initializeTextures();

// Helper function to calculate the scaling factor for the sprites
float calculateScaleFactor(const sf::Texture& texture, int squareSize) {
    sf::Vector2u texSize = texture.getSize();
    float scale = static_cast<float>(squareSize) / texSize.x;
    return scale; // Assuming the texture is square
}

// Function to initialize chess piece sprites and their positions
void initializePieces(std::vector<sf::Sprite>& sprites, int squareSize) {
    // Calculate scale factors based on the first texture loaded
    float scale = 0.5;

    // Definitions of textures for black and white pieces
    std::vector<sf::Texture*> blackTextures = {
        &PieceTexture::blackRook, &PieceTexture::blackKnight, &PieceTexture::blackBishop,
        &PieceTexture::blackQueen, &PieceTexture::blackKing, &PieceTexture::blackBishop,
        &PieceTexture::blackKnight, &PieceTexture::blackRook
    };

    std::vector<sf::Texture*> whiteTextures = {
        &PieceTexture::whiteRook, &PieceTexture::whiteKnight, &PieceTexture::whiteBishop,
        &PieceTexture::whiteQueen, &PieceTexture::whiteKing, &PieceTexture::whiteBishop,
        &PieceTexture::whiteKnight, &PieceTexture::whiteRook
    };

    // Initialize and place black pieces
    for (int i = 0; i < 8; ++i) {
        // Black non-pawn pieces
        sprites.emplace_back(*blackTextures[i]);
        sprites.back().setScale(scale, scale);
        sf::Vector2f centeredPosition(i * squareSize + squareSize / 2.0f, squareSize / 2.0f);
        sprites.back().setOrigin(sprites.back().getLocalBounds().width / 2.0f, sprites.back().getLocalBounds().height / 2.0f);
        sprites.back().setPosition(centeredPosition);

        // Black pawns
        sprites.emplace_back(PieceTexture::blackPawn);
        sprites.back().setScale(scale, scale);
        centeredPosition = sf::Vector2f(i * squareSize + squareSize / 2.0f, 1.5f * squareSize);
        sprites.back().setOrigin(sprites.back().getLocalBounds().width / 2.0f, sprites.back().getLocalBounds().height / 2.0f);
        sprites.back().setPosition(centeredPosition);
    }

    // Initialize and place white pieces
    for (int i = 0; i < 8; ++i) {
        // White non-pawn pieces
        sprites.emplace_back(*whiteTextures[i]);
        sprites.back().setScale(scale, scale);
        sf::Vector2f centeredPosition(i * squareSize + squareSize / 2.0f, 7.5f * squareSize);
        sprites.back().setOrigin(sprites.back().getLocalBounds().width / 2.0f, sprites.back().getLocalBounds().height / 2.0f);
        sprites.back().setPosition(centeredPosition);

        // White pawns
        sprites.emplace_back(PieceTexture::whitePawn);
        sprites.back().setScale(scale, scale);
        centeredPosition = sf::Vector2f(i * squareSize + squareSize / 2.0f, 6.5f * squareSize);
        sprites.back().setOrigin(sprites.back().getLocalBounds().width / 2.0f, sprites.back().getLocalBounds().height / 2.0f);
        sprites.back().setPosition(centeredPosition);
    }
}

int main() {
    initializeTextures();

    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess Board");

    int squareSize = window.getSize().x / 8;
    std::vector<sf::Sprite> pieceSprites;
    initializePieces(pieceSprites, squareSize);

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





/*void printArray(const std::vector<std::vector<std::shared_ptr<ChessPiece>>>& array);
std::shared_ptr<ChessPiece> addChessPiece(ChessBoard& board, ChessPiece& piece, std::vector<int> position);

int main() {
    std::vector<std::shared_ptr<ChessPiece>> pieces; //Array containing all chess pieces.
    ChessBoard board; //The chessboard.

    for (int i = 0; i < 8; i++) { //Add pawns to the board.
        ChessPiece pawnW("PAW", ChessPiece::WHITE); //Pawn
        pieces.push_back(addChessPiece(board, pawnW, {6, i}));

        ChessPiece pawnB("PAW", ChessPiece::BLACK); //Pawn
        pieces.push_back(addChessPiece(board, pawnB, {1, i}));
    }

    printArray(board.getGrid()); //Output the chessboard to the terminal.

    return 0;
}

//Add a chess piece (object) to a chessboard.
std::shared_ptr<ChessPiece> addChessPiece(ChessBoard& board, ChessPiece& piece, std::vector<int> position) {
    if (!verifyPosition(position)) {
        std::cout << "Error! addChessPiece() expected coordinate lower than or equal to 8." << std::endl;
    }
    std::shared_ptr<ChessPiece> piecePtr = std::make_shared<ChessPiece>(std::move(piece));
    board.placePiece(piecePtr, position);
    return piecePtr;
}

//Debugging code: outputs the chessboard, if given "board.getGrid()" as a parameter.
void printArray(const std::vector<std::vector<std::shared_ptr<ChessPiece>>>& array) {
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
*/ 
