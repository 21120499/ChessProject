#include "Moves.h"
#include "Piece.h"

Moves::Moves(Piece* _Dich, Point _start, Point _end) {
    this->Dich = _Dich;
    this->start = _start;
    this->end = _end;
}