#ifndef VISUALS_H
#define VISUALS_H

#include <iostream> 
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>

class PieceTexture {
public:
    static sf::Texture blackKing;
    static sf::Texture blackQueen;
    static sf::Texture blackRook;
    static sf::Texture blackKnight;
    static sf::Texture blackBishop;
    static sf::Texture blackPawn;

    static sf::Texture whiteKing;
    static sf::Texture whiteQueen;
    static sf::Texture whiteRook;
    static sf::Texture whiteKnight;
    static sf::Texture whiteBishop;
    static sf::Texture whitePawn;

    static sf::Texture loadTexture(const std::string& path);
};

// Function to initialize all textures
void initializeTextures();


#endif