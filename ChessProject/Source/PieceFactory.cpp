#include "PieceFactory.h"


Piece* PieceFactory::createPiece(int value)
{
    if (value == 0)
    {
        return nullptr;
    }
    int color = (value < 0) ? -1 : 1;
    int type = value * color;
    switch (type)
    {
    case ROOK:
        return new Rook(color);
    case KNIGHT:
        return new Knight(color);
    case BISHOP:
        return new Bishop(color);
    case QUEEN:
        return new Queen(color);
    case PAWN:
        return new Pawn(color);
    case KING:
        return new King(color);
    default:
        return nullptr;
    }
}