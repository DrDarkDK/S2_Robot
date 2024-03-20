#include <cxxabi.h>
#include "general.h"

std::vector<float> coordsToPosition(std::vector<float> position) {
    float x = position[0]+2;
    float y = position[1]+1.5;

    return {x, y};
}

std::shared_ptr<ChessPiece> addChessPiece(ChessBoard& board, ChessPiece& piece, std::vector<int> position, sf::Texture texture) {
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

void initializePieces(std::vector<sf::Sprite>& sprites, int squareSize, std::vector<std::shared_ptr<ChessPiece>> pieces) {
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

    //NOTES: The below for-loop is WIP to being converted into a mix between the two major updates. Currently, black pawns can be spawned in with a position decided by the ChessPiece class.
    //Other than that, this is still being worked on. Current problem: getting the textures from ChessPiece class instead of the above vectors... (tip: it's difficult).
    //Once the below for-loop is finished, it should be able to handle both black and white pieces at once, without the need for a second for-loop.

    // Initialize and place black pieces
    for (int i = 0; i < pieces.size(); ++i) {
        std::vector<float> positionP = coordsToPosition({pieces[i]->getPosition()[1] * squareSize + squareSize / 2.0f, squareSize / 2.0f});
        std::vector<float> positionNP = coordsToPosition({pieces[i]->getPosition()[1] * squareSize + squareSize / 2.0f, (.5f + float(pieces[i]->getPosition()[0])) * squareSize});

        std::cout << getTypeName(pieces[i]->getTexture()) << " | " << getTypeName(*blackTextures[(i < 8 ? i : 7)]) << std::endl;

        // Black non-pawn pieces
        //sprites.emplace_back(pieces[i]->getTexture()); //Temporary solution since pieces can have a greater size than the texture vector, causing potential exceptions.
        //sprites.back().setScale(scale, scale);
        //sf::Vector2f centeredPosition(positionP[0], positionP[1]);
        //sprites.back().setOrigin(sprites.back().getLocalBounds().width / 2.0f, sprites.back().getLocalBounds().height / 2.0f);
        //sprites.back().setPosition(centeredPosition);

        // Black pawns
        sprites.emplace_back(pieces[i]->getTexture());
        sprites.back().setScale(scale, scale);
        sf::Vector2f centeredPosition = sf::Vector2f(positionNP[0], positionNP[1]);
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
