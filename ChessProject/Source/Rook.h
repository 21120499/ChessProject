#include "Piece.h"

class Rook : public Piece {

public:
    Rook(int color);
    Rook(int color, TypePiece type);
    ~Rook();
    vector<Point> canMove(Piece* board[8][8], Point point);

    // Draw
    void initTexturePiece(int color);
};