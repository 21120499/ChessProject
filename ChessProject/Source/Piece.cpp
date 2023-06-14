#include "Piece.h"

int Piece::getColor()
{
    return this->color;
}

Piece::Piece(int color, TypePiece type)
{
    this->color = color;
    this->type = type;
}

TypePiece Piece::getType()
{
    return this->type;
}

Piece::~Piece()
{
}

// Draw Piece
sf::Texture Piece::getTexturePiece()
{
    return this->texturePiece;
}

sf::Sprite Piece::getSpritePiece()
{
    return this->spritePiece;
}

void Piece::initSpritePiece()
{
    this->spritePiece.setTexture(this->texturePiece);
    spritePiece.setOrigin(spritePiece.getLocalBounds().width / 2, spritePiece.getLocalBounds().height / 2);
}

void Piece::renderPiece(sf::RenderTarget& target)
{
    target.draw(this->spritePiece);
}

void Piece::setPosition(double x, double y)
{
    this->spritePiece.setPosition(y * 100 + 50, x * 100 + 50);
}

void Piece::setTrayPosition(int x, int y) {
    this->spritePiece.setPosition(x, y);
}

void Piece::transformSprite()
{
    if (color == -1)
    {
        if (!this->texturePiece.loadFromFile("Picture/TransformBlack.png"))
        {
            std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
        }
    }
    else if (color == 1)
    {
        if (!this->texturePiece.loadFromFile("Picture/TransformWhite.png"))
        {
            std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
        }
    }

    this->spritePiece.setTexture(this->texturePiece);
    spritePiece.setOrigin(spritePiece.getLocalBounds().width / 2, spritePiece.getLocalBounds().height / 2);
}