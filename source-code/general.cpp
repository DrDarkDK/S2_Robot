#include <cxxabi.h>
#include "general.h"
#include "functionality.h"
#include "visuals.h"

bool verifyPosition(std::vector<int> position) { //Check if a position is inside an 8x8 grid.
    if (position[0] < 8 && position[1] < 8) {
        if (position[0] >= 0 && position[1] >= 0) {
            return true;
        }
    }
    return false;
}

std::vector<int> getCursorPosition(sf::RenderWindow &window) {
    sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
    int clickedX = cursorPos.x / (800 / 8);
      clickedX = clickedX > 8 ? 8 : clickedX;
      clickedX = clickedX < 0 ? 0 : clickedX;
    int clickedY = cursorPos.y / (800 / 8);
      clickedY = clickedY > 8 ? 8 : clickedY;
      clickedY = clickedY < 0 ? 0 : clickedY;

      return {clickedX, clickedY};
}

//createPiece(type, isWhite, texture, position, &board)
void createPiece(std::string type, bool isWhite, sf::Texture& texture, std::vector<int> position, ChessBoard& board) {
    enum Color {
            WHITE,
            BLACK
        };
    
    std::string tag;
    const char *charray = type.c_str(); //Char <-> Array = Charray.
    for (int i = 0; i < type.size() && i < 3; i++) {
        tag += toupper(charray[i]);
    }

    ChessPiece piece(tag, (isWhite ? ChessPiece::WHITE : ChessPiece::BLACK), texture);
    addChessPiece(board, piece, position);
} 

//Convert a set of coordinates into the relevant position on the chessboard (for visualisation purposes).
std::vector<float> coordsToPosition(std::vector<float> position) {
    float x = position[0]+2;
    float y = position[1]+1.5;

    return {x, y};
}

void addChessPiece(ChessBoard& board, ChessPiece& piece, std::vector<int> position) {
    if (!verifyPosition(position)) {
        std::cout << "Error! addChessPiece() expected coordinate lower than or equal to 8." << std::endl;
    }
    std::shared_ptr<ChessPiece> piecePtr = std::make_shared<ChessPiece>(std::move(piece));
    board.placePiece(piecePtr, position);
}

void printGrid(const std::vector<std::vector<std::shared_ptr<ChessPiece>>>& array) {
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


float calculateScaleFactor(const sf::Texture& texture, int squareSize) {
    sf::Vector2u texSize = texture.getSize();
    float scale = static_cast<float>(squareSize) / texSize.x;
    return scale; // Assuming the texture is square
}

void initializePieces(std::vector<sf::Sprite>& sprites, int squareSize, ChessBoard& board) {
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
    for (int i = 0; i < board.getPieces().size(); ++i) {
        std::vector<float> calcPosition;
        std::vector<int> oldPos = board.getPieces()[i]->getPosition();
        
        calcPosition = coordsToPosition({oldPos[1] * squareSize + squareSize / 2.1f, (.5f + float(oldPos[0])) * squareSize});

        sprites.emplace_back(board.getPieces()[i]->getTexture());
        sprites.back().setScale(scale, scale);
        sf::Vector2f centeredPosition = sf::Vector2f(calcPosition[0], calcPosition[1]);
        sprites.back().setOrigin(sprites.back().getLocalBounds().width / 2.0f, sprites.back().getLocalBounds().height / 2.0f);
        sprites.back().setPosition(centeredPosition);
    }
}
