#include <cxxabi.h>
#include "general.h"
#include "functionality.h"
#include "visuals.h"

//createPiece(type, isWhite, texture, position, &board, &pieces)
void createPiece(std::string type, bool isWhite, sf::Texture& texture, std::vector<int> position, ChessBoard& board, std::vector<std::shared_ptr<ChessPiece>>& pieces) {
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
    pieces.push_back(addChessPiece(board, piece, position));
} 

std::vector<float> coordsToPosition(std::vector<float> position) {
    float x = position[0]+2;
    float y = position[1]+1.5;

    return {x, y};
}

std::shared_ptr<ChessPiece> addChessPiece(ChessBoard& board, ChessPiece& piece, std::vector<int> position) {
    if (!verifyPosition(position)) {
        std::cout << "Error! addChessPiece() expected coordinate lower than or equal to 8." << std::endl;
    }
    std::shared_ptr<ChessPiece> piecePtr = std::make_shared<ChessPiece>(std::move(piece));
    board.placePiece(piecePtr, position);
    return piecePtr;
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

void initializePieces(std::vector<sf::Sprite>& sprites, int squareSize, std::vector<std::shared_ptr<ChessPiece>>& pieces) {
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
    for (int i = 0; i < pieces.size(); ++i) {
        std::vector<float> calcPosition;
        if (pieces[i]->getType() == "PAW") {
                calcPosition = coordsToPosition({pieces[i]->getPosition()[1] * squareSize + squareSize / 2.0f, (.5f + float(pieces[i]->getPosition()[0])) * squareSize});
            } else {
                calcPosition = coordsToPosition({pieces[i]->getPosition()[1] * squareSize + squareSize / 2.0f, (float(pieces[i]->getPosition()[1]) * squareSize) / 2.0f});
                std::cout << calcPosition[0] << " | " << calcPosition[1] << std::endl;
        } 

        //std::cout << getTypeName(pieces[i]->getTexture()) << " | " << getTypeName(*blackTextures[(i < 8 ? i : 7)]) << std::endl;

        // Black non-pawn pieces
        //sprites.emplace_back(pieces[i]->getTexture()); //Temporary solution since pieces can have a greater size than the texture vector, causing potential exceptions.
        //sprites.back().setScale(scale, scale);
        //sf::Vector2f centeredPosition(positionP[0], positionP[1]);
        //sprites.back().setOrigin(sprites.back().getLocalBounds().width / 2.0f, sprites.back().getLocalBounds().height / 2.0f);
        //sprites.back().setPosition(centeredPosition);

        // Black pawns
        sprites.emplace_back(pieces[i]->getTexture());
        sprites.back().setScale(scale, scale);
        sf::Vector2f centeredPosition = sf::Vector2f(calcPosition[0], calcPosition[1]);
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
