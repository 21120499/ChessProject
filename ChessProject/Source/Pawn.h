#include "Piece.h"

class Pawn : public Piece
{
public:
    Pawn(int color);
    Pawn(int color, TypePiece type);
    ~Pawn();
    vector<Point> canMove(Piece* board[8][8], Point start);

    // Draw
    void initTexturePiece(int color);
};