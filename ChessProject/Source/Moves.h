#pragma once
#include "Piece.h"

class Moves
{
public:
    Piece* Dich;
    Point start;
    Point end;
    Moves(Piece* _Dich, Point _start, Point _end);
};