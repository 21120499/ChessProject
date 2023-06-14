#include "Piece.h"

class Knight : public Piece
{
public:
    Knight(int color);
    ~Knight();
    vector<Point> canMove(Piece* board[8][8], Point start);

    // Draw Knight
    void initTexturePiece(int color);
};