#include "Board.h"
#include <fstream>
#include "PieceFactory.h"

void Board::initBoard(int a[8][8], int _turn, int _win)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = PieceFactory::createPiece(a[i][j]);
            if (board[i][j] != nullptr)
                this->board[i][j]->setPosition(i, j);
        }
    }
    turn = _turn;
    win = _win;
}

Board::Board()
{
    int a[8][8] =
        {-4, -2, -3, -5, -6, -3, -2, -4,
         -1, -1, -1, -1, -1, -1, -1, -1,
         0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0,
         1, 1, 1, 1, 1, 1, 1, 1,
         4, 2, 3, 5, 6, 3, 2, 4};

    this->initBoard(a, 1, 0);
    this->isTransform = false;
    this->isRender = true;
    this->isMove = false;

    // Draw Board
    this->initTextureBoard();
    this->initSpriteBoard();

    // square directions
    this->initSquareDirection();

    this->initSound();

    this->killedWhitePiece.setPosition(840, 20);
    this->killedBlackPiece.setPosition(840, 620);
    this->killedBlackPiece.initpiecePositions();
    this->killedWhitePiece.initpiecePositions();
}

bool Board::canMoveInBoard(vector<Point> listValidMoves, Point end)
{
    for (int i = 0; i < listValidMoves.size(); i++)
    {
        if (listValidMoves[i] == end)
            return true;
    }

    return false;
}

bool Board::endGame()
{
    int kingBlack = 0;
    int kingWhite = 0;
    // lấy vị trí con vua
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != nullptr)
            {
                int type = board[i][j]->getColor() * board[i][j]->getType();
                if (board[i][j]->getType() == KING)
                {
                    if (board[i][j]->getColor() < 0)
                    {
                        kingBlack++;
                    }
                    else if (board[i][j]->getColor() > 0)
                    {
                        kingWhite++;
                    }
                }
            }
        }
    }

    if (kingBlack != kingWhite)
    {
        win = (kingBlack > kingWhite) ? -1 : 1;
        return true;
        // dựa trên bên nào còn con vua
    }
    // kiểm tra dựa trên số nước có thể đi bên phía lượt = turn
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != nullptr && board[i][j]->getColor() == turn)
            {
                vector<Point> listCanMove = canMove(Point(i, j));
                // nếu tất cả tướng cùng màu có thể di chuyển mà ko bị chiếu tướng thì chưa endgame
                if (listCanMove.size() > 0)
                    return false;
                // nhưng nếu tất cả tướng không thể di chuyển có thể hòa, hoặc thua
            }
        }
    }
    // lúc này tướng cùng màu = turn khong thể di chuyển
    if (checkmate(turn))
    {
        // bị chiếu thì thua
        win = turn * -1;
    } // không thì hòa
    else
        win = 0;
    return true;
}

bool Board::checkmate(int color)
{
    vector<Point> listCheckmate = canLosePiece(color);
    Point kingPos;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != nullptr)
            {
                if (board[i][j]->getType() == KING)
                {
                    if (board[i][j]->getColor() == color)
                        kingPos.set(i, j);
                }
            }
        }
    }
    for (auto i : listCheckmate)
    {
        if (kingPos == i)
        {
            return true;
        }
    }
    return false;
}

vector<Point> Board::canLosePiece(int color)
{
    vector<Point> listCheckmate;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != nullptr && board[i][j]->getColor() == color * -1)
            {
                Piece *pieceStart = board[i][j];
                vector<Point> listP = pieceStart->canMove(board, Point(i, j));
                for (auto p : listP)
                {
                    if (board[i][j]->getType() == PAWN)
                    {
                        if (p.y == j)
                            continue;
                    }
                    bool exist = false;
                    for (int k = 0; k < listCheckmate.size(); k++)
                    {
                        if (p == listCheckmate[k])
                        {
                            exist = true;
                            break;
                        }
                    }
                    if (exist == false)
                        listCheckmate.push_back(p);
                }
            }
        }
    }
    return listCheckmate;
}

Board::~Board()
{
    clearBoard();
}

void Board::clearBoard()
{
    for (Moves i : beforeMoves)
    {
        if (i.Dich != NULL && !(i.start == i.end))
        {
            delete i.Dich;
            i.Dich = NULL;
        }
    }
    beforeMoves.clear();

    for (Moves i : afterMoves)
    {
        if (i.Dich != NULL && (i.start == i.end))
        {
            delete i.Dich;
            i.Dich = NULL;
        }
    }
    afterMoves.clear();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != NULL)
            {
                delete board[i][j];
                board[i][j] = NULL;
            }
        }
    }
}

Piece *&Board::Get(Point a)
{
    return board[a.x][a.y];
}

void Board::Undo()
{
    if (beforeMoves.size() <= 0)
    {
        cout << "Day la nuoc di dau tien!" << endl;
        return;
    }

    Moves last = beforeMoves.back();
    afterMoves.push_back(beforeMoves.back());
    beforeMoves.pop_back();

    // is pawn go to the end
    if (last.start == last.end)
    {
        // quan tot di xuong cuoi
        board[last.end.x][last.end.y] = PieceFactory::createPiece(-PAWN * turn);
        last = beforeMoves.back();
        afterMoves.push_back(beforeMoves.back());
        beforeMoves.pop_back();
    }

    // swap positions
    if (last.Dich != NULL)
    {
        if (this->turn > 0)
        {
            this->killedWhitePiece.removeLastPiece();
        }
        else
        {
            this->killedBlackPiece.removeLastPiece();
        }
    }

    Get(last.start) = Get(last.end);
    Get(last.end) = last.Dich;

    // graphic
    if (this->board[last.end.x][last.end.y])
        this->board[last.end.x][last.end.y]->spritePiece.setPosition(last.end.y * 100 + 50, last.end.x * 100 + 50);

    this->board[last.start.x][last.start.y]->spritePiece.setPosition(last.start.y * 100 + 50, last.start.x * 100 + 50);
    this->board[-1][-1] = nullptr;
    this->start.x = -1;
    this->start.y = -1;
    this->squareDirections.clear();

    turn *= -1;
}

void Board::Redo()
{
    if (afterMoves.size() <= 0)
    {
        cout << "Khong co nuoc di nao o sau!" << endl;
        return;
    }
    // get moves
    Moves last = afterMoves.back();
    beforeMoves.push_back(afterMoves.back());
    afterMoves.pop_back();

    Point start = last.start;
    Point end = last.end;

    // check whether the end point has piece to sound
    Piece *killedPiece = this->board[end.x][end.y];
    if (!killedPiece)
    {
        this->movePieceSound.play();
    }
    else
    {
        this->killOtherPieceSound.play();
        if (killedPiece->getColor() > 0)
        {
            this->killedWhitePiece.addPiece(killedPiece);
        }
        else
        {
            this->killedBlackPiece.addPiece(killedPiece);
        }
    }

    // swap positions
    board[end.x][end.y] = board[start.x][start.y];
    board[start.x][start.y] = nullptr;


    // graphic
    this->board[end.x][end.y]->spritePiece.setPosition(end.y * 100 + 50, end.x * 100 + 50);
    this->start.x = start.x;
    this->start.y = start.y;
    this->squareDirections.clear();

    // check when has afterMoves and piece is not pawn and end
    if (board[end.x][end.y]->getType() != PAWN)
    {
        turn *= -1;

        // check mate and end game
        if (this->checkmate(this->turn))
        {
            this->beInCheckSound.play();
        }

        return;
    }

    // is Pawn if go to the end
    if (afterMoves.size() > 0)
    {
        Moves next = afterMoves.back();
        if (next.end == next.start)
        {
            this->start = next.start;
            this->end = next.end;
            // delete that PAWN to asign new Piece
            delete board[end.x][end.y];
            board[end.x][end.y] = next.Dich;


            // return the position from tray
            this->board[end.x][end.y]->spritePiece.setPosition(end.y * 100 + 50, end.x * 100 + 50);

            // if redo then add this Moves to beforeMoves ,remove Moves from after
            beforeMoves.push_back(afterMoves.back());
            afterMoves.pop_back();
        }
    }

    turn *= -1;

    // check mate and end game
    if (this->checkmate(this->turn))
    {
        this->beInCheckSound.play();
    }
}

int Board::getTurn()
{
    return this->turn;
}

bool Board::saveGame()
{
    ofstream f("savegame.txt");
    if (!f.is_open())
        return false;
    f << this->type << endl;
    f << this->turn << endl;
    f << this->win << endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != nullptr)
            {
                if (board[i][j]->getColor() == 1)
                    f << board[i][j]->getColor() * board[i][j]->getType() << "   ";
                else
                    f << board[i][j]->getColor() * board[i][j]->getType() << "  ";
            }
            else
                f << "0   ";
        }
        f << endl;
    }

    f << beforeMoves.size() << endl;
    for (Moves i : beforeMoves)
    {
        if (i.Dich != NULL)
        {
            f << i.Dich->getColor() * i.Dich->getType();
        }
        else
            f << 0;
        f << " " << i.start.x << " " << i.start.y << " " << i.end.x << " " << i.end.y << endl;
    }

    f << afterMoves.size() << endl;
    for (Moves i : afterMoves)
    {
        if (i.Dich != NULL)
        {
            f << i.Dich->getColor() * i.Dich->getType();
        }
        else
            f << 0;
        f << " " << i.start.x << " " << i.start.y << " " << i.end.x << " " << i.end.y << endl;
    }
    return true;
}

bool Board::loadGame()
{
    ifstream f("savegame.txt");
    if (!f.is_open() || f.eof())
        return false;
    int _turn, _win;
    f >> this->type; // mặc định 0 là chơi với người 1 là máy

    f >> _turn;
    f >> _win;
    int a[8][8]{0};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            f >> a[i][j];
        }
    }
    if (f.eof())
        return false;
    clearBoard();
    initBoard(a, _turn, _win);

    // reset trays
    this->killedWhitePiece.reset();
    this->killedBlackPiece.reset();

    int bfSize, aftSize;
    f >> bfSize;
    for (int i = 0; i < bfSize; i++)
    {
        Piece *_Dich;
        int _type;
        Point _start;
        Point _end;
        f >> _type;
        _Dich = PieceFactory::createPiece(_type);
        f >> _start.x >> _start.y;
        f >> _end.x >> _end.y;

        
        if (_Dich != nullptr)
        {   
            // graphic
            _Dich->setPosition(_end.x, _end.y);

            // load for piece trays
            if (_start == _end)
            {
                // skip
            }
            else
            {
                _type > 0 ? this->killedWhitePiece.addPiece(_Dich): this->killedBlackPiece.addPiece(_Dich);
            }
        }

        Moves a(_Dich, _start, _end);
        this->beforeMoves.push_back(a);
    }
    f >> aftSize;
    for (int i = 0; i < aftSize; i++)
    {
        Piece *_Dich;
        int _type;
        f >> _type;
        Point _start;
        _Dich = PieceFactory::createPiece(_type);
        f >> _start.x >> _start.y;
        Point _end;
        f >> _end.x >> _end.y;

        if (_Dich != nullptr)
        {
            _Dich->setPosition(_end.x, _end.y);

        }

        Moves a(_Dich, _start, _end);
        this->afterMoves.push_back(a);
    }

    // graphic
    this->isRender = true;
    this->board[-1][-1] = nullptr;
    this->start.x = -1;
    this->start.y = -1;
    this->squareDirections.clear();
    return true;
}

// Graphic
void Board::transformPawn(sf::Vector2f mousePosView)
{
    if (this->board[end.x][end.y]->spritePiece.getGlobalBounds().contains(mousePosView))
    {
        this->isTransform = false;
        delete this->board[end.x][end.y];

        if (mousePosView.x >= end.y * 100 && mousePosView.x < (end.y + 0.5) * 100 && mousePosView.y >= end.x * 100 && mousePosView.y < (end.x + 0.5) * 100)
        {
            this->board[end.x][end.y] = PieceFactory::createPiece(ROOK * turn);
        }
        else if (mousePosView.x >= (end.y + 0.5) * 100 && mousePosView.x <= (end.y + 1) * 100 && mousePosView.y >= end.x * 100 && mousePosView.y < (end.x + 0.5) * 100)
        {
            this->board[end.x][end.y] = PieceFactory::createPiece(QUEEN * turn);
        }
        else if (mousePosView.x >= end.y * 100 && mousePosView.x < (end.y + 0.5) * 100 && mousePosView.y >= (end.x + 0.5) * 100 && mousePosView.y <= (end.x + 1) * 100)
        {
            this->board[end.x][end.y] = PieceFactory::createPiece(BISHOP * turn);
        }
        else if (mousePosView.x >= (end.y + 0.5) * 100 && mousePosView.x <= (end.y + 1) * 100 && mousePosView.y >= (end.x + 0.5) * 100 && mousePosView.y <= (end.x + 1) * 100)
        {
            this->board[end.x][end.y] = PieceFactory::createPiece(KNIGHT * turn);
        }

        this->board[end.x][end.y]->spritePiece.setPosition(end.y * 100 + 50, end.x * 100 + 50);
        this->turn *= -1;

        if (checkmate(turn))
            this->beInCheckSound.play();

        Moves mv2(Get(end), end, end);
        beforeMoves.push_back(mv2);
    }
}

void Board::savePointStart(sf::Vector2f mousePosView)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (this->board[i][j] != nullptr && this->board[i][j]->spritePiece.getGlobalBounds().contains(mousePosView))
            {
                if (this->board[i][j]->getColor() == this->turn)
                {
                    this->isMove = true;
                    this->start.x = i;
                    this->start.y = j;

                    this->choosePieceSound.play();

                    // square Direction
                    // vector<Point> listValidMoves = this->board[i][j]->canMove(this->board, start);

                    vector<Point> listValidMoves = this->canMove(start);
                    this->createSquareDirections(listValidMoves);
                }
            }
        }
    }
}

Point Board::getPositionPiece(sf::Vector2f mousePosView)
{
    Point location;
    location.x = (int)mousePosView.x / 100;
    location.y = (int)mousePosView.y / 100;
    return location;
}

vector<Point> Board::canMove(Point start)
{
    vector<Point> listValidMoves = board[start.x][start.y]->canMove(board, start);
    int i = 0;

    while (i < listValidMoves.size())
    {
        Point end = listValidMoves[i];
        Piece *tmp = board[end.x][end.y];
        board[end.x][end.y] = board[start.x][start.y];
        board[start.x][start.y] = nullptr;
        if (checkmate(turn))
        {
            listValidMoves.erase(listValidMoves.begin() + i);
            i--;
        }
        board[start.x][start.y] = board[end.x][end.y];
        board[end.x][end.y] = tmp;
        i++;
    }
    return listValidMoves;
}

void Board::Move(sf::Vector2f mousePosView)
{
    this->isMove = false;

    Point location = getPositionPiece(mousePosView); // x y is different i j
    if (location.x < 0 || location.x > 8 || location.y < 0 || location.y > 8)
        return;

    if (this->isTransform == false)
    {
        this->end.x = location.y;
        this->end.y = location.x;
    }

    Piece *pieceStart = this->board[start.x][start.y];
    if (pieceStart == nullptr)
        return;
    vector<Point> listValidMoves = canMove(start);
    // vector<Point> listValidMoves = board[start.x][start.y]->canMove(board, start);
    if (this->canMoveInBoard(listValidMoves, end))
    {
        // xoa nuoc di sau neu thuc hien 1 nuoc di moi khac redo
        if (afterMoves.size() > 0)
        {
            for (auto i : afterMoves)
            {
                if (i.start == i.end)
                    delete i.Dich;
            }
            afterMoves.clear();
        }

        // save moves
        Moves mv(Get(end), start, end);
        beforeMoves.push_back(mv);

        // check whether the end point has piece to sound
        // and add to killed piece tray
        Piece *killedPiece = this->board[end.x][end.y];
        if (!killedPiece)
        {
            this->movePieceSound.play();
        }
        else
        {
            this->killOtherPieceSound.play();
            if (killedPiece->getColor() > 0)
            {
                this->killedWhitePiece.addPiece(killedPiece);
            }
            else
            {
                this->killedBlackPiece.addPiece(killedPiece);
            }
        }

        // swap positions
        this->board[end.x][end.y] = this->board[start.x][start.y];
        this->board[start.x][start.y] = nullptr;

        // set sprite
        this->board[end.x][end.y]->spritePiece.setPosition(location.x * 100 + 50, location.y * 100 + 50);

        // is Pawn at the end of board
        if (this->Get(end)->getType() == PAWN)
        {
            if ((end.x == 7 && this->Get(end)->getColor() == -1) ||
                (end.x == 0 && this->Get(end)->getColor() == 1))
            {

                this->board[end.x][end.y]->transformSprite();
                this->isTransform = true;
            }
        }

        // square directions
        this->squareDirections.erase(this->squareDirections.begin(), this->squareDirections.end());

        // set turn
        if (this->isTransform == false)
        {
            this->turn *= -1;
        }

        // check mate and end game
        if (this->checkmate(this->turn))
        {
            this->beInCheckSound.play();
        }

        if (this->endGame())
        {
            this->winGameSound.play();
        }

        // cout << this->turn << endl;
    }
    else
    {
        this->board[start.x][start.y]->spritePiece.setPosition(start.y * 100 + 50, start.x * 100 + 50); // return point start
    }
}

void Board::updateMove(sf::Vector2f mousePosView)
{
    if (this->isMove)
    {
        this->board[start.x][start.y]->spritePiece.setPosition(mousePosView.x, mousePosView.y);
        this->isRender = true;
    }
}

// Square Direction
void Board::initSquareDirection()
{
    this->squareDirection.setRadius(10);
    this->squareDirection.setFillColor(sf::Color(192, 192, 192));
    this->squareDirection.setOrigin(squareDirection.getRadius(), squareDirection.getRadius());

    this->squareDirectionKill.setRadius(10);
    this->squareDirectionKill.setFillColor(sf::Color::Red);
    this->squareDirectionKill.setOrigin(squareDirectionKill.getRadius(), squareDirectionKill.getRadius());
}

void Board::createSquareDirections(vector<Point> listValidMoves)
{
    this->squareDirections.erase(this->squareDirections.begin(), this->squareDirections.end());
    for (int i = 0; i < listValidMoves.size(); i++)
    {
        Point endMovePoint = listValidMoves[i];

        if (!this->board[endMovePoint.x][endMovePoint.y])
        {
            this->squareDirection.setPosition(endMovePoint.y * 100 + 50, endMovePoint.x * 100 + 50);
            this->squareDirections.push_back(this->squareDirection);
        }
        else
        {
            this->squareDirectionKill.setPosition(endMovePoint.y * 100 + 50, endMovePoint.x * 100 + 50);
            this->squareDirections.push_back(this->squareDirectionKill);
        }
    }
}

// Draw Board
void Board::initTextureBoard()
{
    if (!this->textureBoard.loadFromFile("Picture/Board.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file."
                  << "\n";
    }
}

void Board::initSpriteBoard()
{
    this->spriteBoard.setTexture(this->textureBoard);
}

void Board::renderBoard(sf::RenderTarget &target)
{
    target.draw(this->spriteBoard);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != nullptr)
            {
                board[i][j]->renderPiece(target);
            }
        }
    }

    this->killedWhitePiece.drawTo(target);
    this->killedBlackPiece.drawTo(target);
}

// Draw Square Direction
void Board::renderSquareDirecitons(sf::RenderTarget &target)
{
    for (int i = 0; i < this->squareDirections.size(); i++)
    {
        target.draw(this->squareDirections[i]);
    }
}

void Board::initSound()
{

    if (!this->movePS_buffer.loadFromFile("Asset/moveSound.wav"))
    {
        std::cout << "Cannot load sound in Board class" << std::endl;
    }
    else
    {
        this->movePieceSound.setBuffer(movePS_buffer);
    }

    if (!this->choosePieceSound_buffer.loadFromFile("Asset/choosePiece.wav"))
    {
        std::cout << "Cannot load sound in Board class" << std::endl;
    }
    else
    {
        this->choosePieceSound.setBuffer(choosePieceSound_buffer);
    }

    if (!this->killOtherPieceSound_buffer.loadFromFile("Asset/killOtherPiece.wav"))
    {
        std::cout << "Cannot load sound in Board class" << std::endl;
    }
    else
    {
        this->killOtherPieceSound.setBuffer(killOtherPieceSound_buffer);
    }

    if (!this->beInCheckSound_buffer.loadFromFile("Asset/beInCheck.wav"))
    {
        std::cout << "Load sound in Board class cannnot" << std::endl;
    }
    else
    {
        this->beInCheckSound.setBuffer(beInCheckSound_buffer);
    }

    if (!this->winGameSound_buffer.loadFromFile("Asset/winGame.wav"))
    {
        std::cout << "Load sound in Board class cannnot" << std::endl;
    }
    else
    {
        this->winGameSound.setBuffer(winGameSound_buffer);
    }

    this->setSoundEffectVolume(50);
}

void Board::setSoundEffectVolume(int volume)
{
    this->soundEffectVolume = volume;
    this->choosePieceSound.setVolume(volume);
    this->choosePieceSound.setVolume(volume);
    this->movePieceSound.setVolume(volume);
    this->killOtherPieceSound.setVolume(volume);
    this->beInCheckSound.setVolume(volume);
    this->winGameSound.setVolume(volume);
}

// machine
void Board::MoveMachine()
{
    Point start;
    Point end;
    Find(start, end);
    // xoa nuoc di sau neu thuc hien 1 nuoc di moi khac redo
    if (afterMoves.size() > 0)
    {
        for (auto i : afterMoves)
        {
            if (i.start == i.end)
                delete i.Dich;
        }
        afterMoves.clear();
    }

    // save moves
    Moves mv(Get(end), start, end);
    beforeMoves.push_back(mv);

    Piece *killedPiece = this->board[end.x][end.y];
    if (!killedPiece)
    {
        this->movePieceSound.play();
    }
    else
    {
        this->killOtherPieceSound.play();
        if (killedPiece->getColor() > 0)
        {
            this->killedWhitePiece.addPiece(killedPiece);
        }
        else
        {
            this->killedBlackPiece.addPiece(killedPiece);
        }
    }

    // swap positions
    board[end.x][end.y] = board[start.x][start.y];
    board[start.x][start.y] = nullptr;

    // set sprite
    this->board[end.x][end.y]->spritePiece.setPosition(end.y * 100 + 50, end.x * 100 + 50);

    // is Pawn at the end of board
    if (Get(end)->getType() == PAWN)
    {
        if ((end.x == 7 && Get(end)->getColor() == -1) ||
            (end.x == 0 && Get(end)->getColor() == 1))
        {
            time_t currentTime = time(nullptr);
            srand(static_cast<unsigned int>(currentTime));

            int type = rand() % 4 + 2;
            ;

            type *= turn;
            delete board[end.x][end.y];

            board[end.x][end.y] = PieceFactory::createPiece(type);
            this->board[end.x][end.y]->spritePiece.setPosition(end.y * 100 + 50, end.x * 100 + 50);
            Moves mv2(Get(end), end, end);
            beforeMoves.push_back(mv2);
        }
    }
    turn *= -1;
    // check mate and end game
    if (this->checkmate(this->turn))
    {
        this->beInCheckSound.play();
    }

    if (this->endGame())
    {
        this->winGameSound.play();
    }
}

void Board::Find(Point &start, Point &end)
{
    // bị tướng có thể bị ăn
    vector<Point> canLose = canLosePiece(turn);
    vector<Point> canGet = canLosePiece(-1 * turn);
    // độ an toàn các vị trí
    float tb = 0;
    vector<Point> mine[8][8];
    float a[8][8]{0};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != nullptr)
            {
                if (board[i][j]->getColor() == turn * -1) // check turn is not the same
                {
                    vector<Point> listValidMoves = canMove(Point(i, j));
                    for (auto k : listValidMoves)
                    {
                        a[k.x][k.y] -= board[i][j]->getType();
                        if (Get(k) != NULL && Get(k)->getType() == KING)
                        {
                            a[k.x][k.y] -= 100;
                        }
                        tb -= board[i][j]->getType();
                    }
                }
                else if (board[i][j]->getColor() == turn) // check turn is of player
                {
                    vector<Point> listValidMoves = canMove(Point(i, j));
                    for (auto k : listValidMoves)
                    {

                        a[k.x][k.y] += board[i][j]->getType();
                        if (Get(k) != NULL && Get(k)->getType() == KING)
                        {
                            a[k.x][k.y] += 100;
                        }
                        tb += board[i][j]->getType();
                        mine[k.x][k.y].push_back(Point(i, j));
                    }
                }
            }
        }
    }
    tb /= 8 * 8;

    //-------------CAN-GET-ENEMY-PIECE------------
    bool _canGet = false;
    for (Point p : canGet)
    {
        if (Get(p) != NULL)
        {
            _canGet = true;
            break;
        }
    }

    if (canGet.size() > 0 && _canGet)
    {
        end = Chose(canGet, 1);

        if (mine[end.x][end.y].size() > 0)
        {
            start = Chose(mine[end.x][end.y], -1);
            if (Get(start) != NULL)
            {
                if (mine[end.x][end.y].size() >= 2 || Get(start)->getType() <= Get(end)->getType())
                {
                    cout << "An quan dich" << endl;
                    return;
                }
            }
        }
    }
    //-DEFAULT------------FIND-THE-START---------------
    vector<Point> shouldRun;
    vector<Point> canChose;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != nullptr && board[i][j]->getColor() == turn) // check turn is of player
            {
                // find start
                if (a[i][j] < 0)
                    shouldRun.push_back(Point(i, j));
                canChose.push_back(Point(i, j));
            }
        }
    }
    // run
    Point des;
    vector<Point> canM;
    if (shouldRun.size() > 0)
    {
        des = Chose(shouldRun, 1); // chọn vị trí con quan trọng nhất
        start = des;
        canM = canMove(start);
        for (Point p : canLose)
        {
            auto its = find(canM.begin(), canM.end(), p);
            // Kiểm tra nếu phần tử được tìm thấy
            if (its != canM.end())
            {
                // Xóa phần tử khỏi vector
                canM.erase(its);
            }
        }
    }
    Point min(7, 7);
    if (canM.size() == 0)
    {
        cout << "Default" << endl;
        // trường họp mặc định

        while (Get(min) == NULL || (Get(min) != NULL && (canM.size() == 0 || Get(min)->getColor() != turn)))
        {
            a[min.x][min.y] += tb + 20;
            for (Point p : canChose)
            {
                if (a[p.x][p.y] < a[min.x][min.y])
                {
                    // nguy hiểm nhất
                    min = p;
                }
            }
            start = min;
            canM = canMove(start);
        }
    }
    if (a[start.x][start.y] >= 0)
    {
        cout << "Khong co uy hiep" << endl;
        min = Chose(canChose, -1);
        start = min;
        canM = canMove(start);
        while (canM.size() == 0)
        {
            auto its = find(canChose.begin(), canChose.end(), min);
            // Kiểm tra nếu phần tử được tìm thấy
            if (its != canChose.end())
            {
                // Xóa phần tử khỏi vector
                canChose.erase(its);
            }
            min = Chose(canChose, -1);
            // gan start moi
            start = min;
            canM = canMove(start);
        }
    }

    //-------------FIND-THE-END---------------
    vector<Point> canSwallow = canM;
    end = Chose(canSwallow, 1);

    for (Point p : canLose)
    {
        auto its = find(canSwallow.begin(), canSwallow.end(), p);
        // Kiểm tra nếu phần tử được tìm thấy
        if (its != canSwallow.end())
        {
            // Xóa phần tử khỏi vector
            canSwallow.erase(its);
        }
    }
    if (canSwallow.size() == 0)
    {
        end = Chose(canM, 1);
    }
    else
    {
        end = Chose(canSwallow, 1);
    }
    return;
}

Point Board::Chose(vector<Point> list, int vector)
{
    // vector <0 chọn tướng ưu tiên thấp nhất, >0 chọn ưu tiên cao nhất
    int index = 0;
    Point p = list.back();
    bool allNull = true;
    for (Point i : list)
    {
        if (Get(i) != NULL)
        {
            p = i;
            allNull = false;
            break;
        }
    }
    if (allNull)
        return p;
    if (vector < 0)
    {
        for (Point i : list)
        {
            if (Get(i) != NULL && Get(i)->getType() < Get(p)->getType())
            {
                p = i;
            }
        }
    }
    else
    {
        for (Point i : list)
        {
            if (Get(i) != NULL && Get(i)->getType() > Get(p)->getType())
            {
                p = i;
            }
        }
    }
    return p;
}
