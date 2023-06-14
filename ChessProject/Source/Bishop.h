#include "Piece.h"

class Bishop : public Piece {

public:
    Bishop(int color);
    Bishop(int color, TypePiece type);
    ~Bishop();
    bool canMove(Point start, Point end);
    vector<Point> canMove(Piece* board[8][8], Point point);

    // Draw
    void initTexturePiece(int color);
};