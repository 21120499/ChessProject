#include "Piece.h"

class Queen : public Piece
{
public:
    Queen(int color);
    ~Queen();
    vector<Point> canMove(Piece* board[8][8], Point start);

    // Draw Queen
    void initTexturePiece(int color);
};

