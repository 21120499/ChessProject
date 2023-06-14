#include "King.h"

King::King(int color) : Piece(color, KING)
{
    this->initTexturePiece(color);
    this->initSpritePiece();
}

King::King(int color, TypePiece type) : Piece(color, type)
{
}


King::~King()
{
}

vector<Point> King::canMove(Piece* board[8][8], Point start)
{
    vector<Point> listValidMoves;

    Piece* pieceStart = board[start.x][start.y];
    if (pieceStart == nullptr)
        return listValidMoves;

    Point step;
    int stepX[8] = { 0, 0, 1, -1, 1, -1, 1, -1 };
    int stepY[8] = { 1, -1, 0, 0, 1, -1, -1, 1 };

    for (int i = 0; i < 8; i++)
    {
        step.x = start.x + stepX[i];
        step.y = start.y + stepY[i];
        if (step.x >= 0 && step.x < 8 && step.y >= 0 && step.y < 8)
        {
            if (board[step.x][step.y] != nullptr)
            {
                if (board[step.x][step.y]->getColor() == board[start.x][start.y]->getColor())
                    continue;
                else
                {
                    listValidMoves.push_back(step);
                    continue;
                }
            }
            listValidMoves.push_back(step);
        }
    }

    return listValidMoves;
}

// Draw
void King::initTexturePiece(int color)
{
    if (color == -1)
    {
        if (!this->texturePiece.loadFromFile("Picture/KingBlack.png"))
        {
            std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
        }
    }
    else if (color == 1)
    {
        if (!this->texturePiece.loadFromFile("Picture/KingWhite.png"))
        {
            std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
        }
    }
}