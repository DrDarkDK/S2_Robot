#include "visuals.h"

// --- PIECETEXTURE CLASS ---

// Definitions of static textures
sf::Texture PieceTexture::blackKing;
sf::Texture PieceTexture::blackQueen;
sf::Texture PieceTexture::blackRook;
sf::Texture PieceTexture::blackKnight;
sf::Texture PieceTexture::blackBishop;
sf::Texture PieceTexture::blackPawn;

sf::Texture PieceTexture::whiteKing;
sf::Texture PieceTexture::whiteQueen;
sf::Texture PieceTexture::whiteRook;
sf::Texture PieceTexture::whiteKnight;
sf::Texture PieceTexture::whiteBishop;
sf::Texture PieceTexture::whitePawn;

sf::Texture PieceTexture::loadTexture(const std::string& path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Could not load texture from " << path << std::endl;
        exit(EXIT_FAILURE); // Exit if we cannot load the texture
    }
    return texture;
}

void initializeTextures() { //This will ONLY work if your terminal directory is in the S2_Robot path. It can't be in a sub-directory.
    PieceTexture::blackKing = PieceTexture::loadTexture("../source-code/Assets/b_king.png");
    PieceTexture::blackQueen = PieceTexture::loadTexture("../source-code/Assets/b_queen.png");
    PieceTexture::blackRook = PieceTexture::loadTexture("../source-code/Assets/b_rook.png");
    PieceTexture::blackKnight = PieceTexture::loadTexture("../source-code/Assets/b_knight.png");
    PieceTexture::blackBishop = PieceTexture::loadTexture("../source-code/Assets/b_bishop.png");
    PieceTexture::blackPawn = PieceTexture::loadTexture("../source-code/Assets/b_pawn.png");

    PieceTexture::whiteKing = PieceTexture::loadTexture("../source-code/Assets/w_king.png");
    PieceTexture::whiteQueen = PieceTexture::loadTexture("../source-code/Assets/w_queen.png");
    PieceTexture::whiteRook = PieceTexture::loadTexture("../source-code/Assets/w_rook.png");
    PieceTexture::whiteKnight = PieceTexture::loadTexture("../source-code/Assets/w_knight.png");
    PieceTexture::whiteBishop = PieceTexture::loadTexture("../source-code/Assets/w_bishop.png");
    PieceTexture::whitePawn = PieceTexture::loadTexture("../source-code/Assets/w_pawn.png");
}