#pragma once
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Point.h"
using namespace std;

enum TypePiece
{
    PAWN = 1,
    KNIGHT = 2,
    BISHOP = 3,
    ROOK = 4,
    QUEEN = 5,
    KING = 6
};

class Piece
{
private:
    int color; // 1: white, -1: black
    TypePiece type;

public:
    Piece(int color, TypePiece type);
    virtual ~Piece();
    virtual vector<Point> canMove(Piece* board[8][8], Point start) = 0;
    int getColor();
    TypePiece getType();

    // Draw Piece
    sf::Texture texturePiece;
    sf::Sprite spritePiece;

    sf::Texture getTexturePiece();
    sf::Sprite getSpritePiece();

    virtual void initTexturePiece(int color) = 0;
    void setPosition(double x, double y);
    void setTrayPosition(int x, int y);
    void initSpritePiece();
    void renderPiece(sf::RenderTarget& target);
    void transformSprite();
};

