#include "Rook.h"

Rook::Rook(int color) : Piece::Piece(color, ROOK) 
{
    this->initTexturePiece(color);
    this->initSpritePiece();
}
Rook::Rook(int color, TypePiece type) : Piece::Piece(color, type) { }
Rook::~Rook() {}

vector<Point> Rook::canMove(Piece* board[8][8], Point point) {

    vector<Point> validMoves;

    Piece* chosenPiece = board[point.x][point.y];
    if (!chosenPiece)
        return validMoves;

    Point step;
    int horizontalStepX[4] = { 0, 0, 1, -1 }; // up, down, right left
    int horizontalStepY[4] = { 1, -1, 0, 0 };

    for (int i = 0; i < 4; i++)
    {
        step.x = point.x + horizontalStepX[i];
        step.y = point.y + horizontalStepY[i];
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
            step.x += horizontalStepX[i];
            step.y += horizontalStepY[i];
        }
    }

    return validMoves;
}

// Draw
void Rook::initTexturePiece(int color)
{
    if (color == -1)
    {
        if (!this->texturePiece.loadFromFile("Picture/RookBlack.png"))
        {
            std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
        }
    }
    else if (color == 1)
    {
        if (!this->texturePiece.loadFromFile("Picture/RookWhite.png"))
        {
            std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
        }
    }
}