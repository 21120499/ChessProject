#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Piece.h"

class PieceTray
{
private:
    std::vector<Piece *> pieceInTray;
    Point trayPoint;
    std::vector<Point> piecePositions;
    int numOfPiece;

public:
    PieceTray();
    void initpiecePositions();
    void addPiece(Piece *piece);
    void removeLastPiece();
    void resizePieceSpriteOut(Piece *piece);
    void resizePieceSpriteIn(Piece *piece);
    void drawTo(sf::RenderTarget &target);
    void setPosition(int x, int y);
    int getSize();
    void reset();
};