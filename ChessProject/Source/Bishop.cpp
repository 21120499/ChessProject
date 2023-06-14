#include "Bishop.h"

Bishop::Bishop(int color, TypePiece type) : Piece::Piece(color, type) 
{
}
Bishop::Bishop(int color) : Piece::Piece(color, BISHOP) 
{
    this->initTexturePiece(color);
    this->initSpritePiece();
}

bool Bishop::canMove(Point start, Point end) {

    int sub1 = abs(start.x - end.x);
    int sub2 = abs(start.y - end.y);

    return sub1 == sub2;

}

Bishop::~Bishop() {}

vector<Point> Bishop::canMove(Piece* board[8][8], Point point) {

    vector<Point> validMoves;

    int diagonalStepX[4] = { 1, 1, -1, -1 };
    int diagonalStepY[4] = { 1, -1, 1, -1 };
    Point step;

    for (int i = 0; i < 4; i++)
    {
        step.x = point.x + diagonalStepX[i];
        step.y = point.y + diagonalStepY[i];
        while (step.x >= 0 && step.x < 8 && step.y >= 0 && step.y < 8)
        {
            if (board[step.x][step.y] != NULL)
            {
                if (board[step.x][step.y]->getColor() == board[point.x][point.y]->getColor()) {
                    break;
                }
                else {
                    validMoves.push_back(step);
                    break;
                }
            }
            validMoves.push_back(step);
            step.x += diagonalStepX[i];
            step.y += diagonalStepY[i];
        }
    }
    return validMoves;
}

// Draw
void Bishop::initTexturePiece(int color)
{
    if (color == -1)
    {
        if (!this->texturePiece.loadFromFile("Picture/BishopBlack.png"))
        {
            std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
        }
    }
    else if (color == 1)
    {
        if (!this->texturePiece.loadFromFile("Picture/BishopWhite.png"))
        {
            std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
        }
    }
}