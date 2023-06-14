#include "Piece.h"

class King : public Piece
{
public:
    King(int color);
    King(int color, TypePiece type);
    ~King();
    vector<Point> canMove(Piece* board[8][8], Point start);

    // Draw
    void initTexturePiece(int color);
};