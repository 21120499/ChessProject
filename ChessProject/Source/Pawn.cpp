#include "Pawn.h"

Pawn::Pawn(int color) : Piece(color, PAWN)
{
    this->initTexturePiece(color);
    this->initSpritePiece();
}

Pawn::Pawn(int color, TypePiece type) : Piece(color, type)
{
}

Pawn::~Pawn()
{
}

vector<Point> Pawn::canMove(Piece* board[8][8], Point start)
{
    vector<Point> listValidMoves;

    Piece* pieceStart = board[start.x][start.y];
    if (pieceStart == nullptr)
        return listValidMoves;

    Point step;
    int direction = -1 * pieceStart->getColor();

    // Move forward
    step.x = start.x + direction;
    step.y = start.y;
    if (step.x >= 0 && step.x < 8 && step.y >= 0 && step.y < 8)
    {
        if (board[step.x][step.y] == nullptr)
        {
            listValidMoves.push_back(step);

            // Move two squares forward if it's the pawn's first move
            if ((start.x == 1 && direction == 1) || (start.x == 6 && direction == -1))
            {
                step.x += direction;
                if (board[step.x][step.y] == nullptr)
                    listValidMoves.push_back(step);
            }
        }
    }

    // Capture diagonally
    int diagonalStepY[2] = { 1, -1 };
    for (int i = 0; i < 2; i++)
    {
        step.x = start.x + direction;
        step.y = start.y + diagonalStepY[i];
        if (step.x >= 0 && step.x < 8 && step.y >= 0 && step.y < 8)
        {
            if (board[step.x][step.y] != nullptr)
            {
                if (board[step.x][step.y]->getColor() != board[start.x][start.y]->getColor())
                    listValidMoves.push_back(step);
            }
        }
    }

    return listValidMoves;
}

// Draw
void Pawn::initTexturePiece(int color)
{
    if (color == -1)
    {
        if (!this->texturePiece.loadFromFile("Picture/PawnBlack.png"))
        {
            std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
        }
    }
    else if (color == 1)
    {
        if (!this->texturePiece.loadFromFile("Picture/PawnWhite.png"))
        {
            std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
        }
    }
}
