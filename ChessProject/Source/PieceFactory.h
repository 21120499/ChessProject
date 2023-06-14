#pragma once
#include "Queen.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Pawn.h"

class Piece;
class PieceFactory
{
public:
    static Piece* createPiece(int value);
};