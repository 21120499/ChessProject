#pragma once
#include "PieceFactory.h"
#include "SFML/Audio.hpp"
#include "Moves.h"
#include "PieceTray.h"

class Board
{
public:
    Piece *board[8][8];
    int type;// mặc định 0 là chơi với người 1 là máy
    int turn;
    int win; // 1: White win, -1: Black win 0: Draw
    vector<Moves> beforeMoves;
    vector<Moves> afterMoves;

    // Draw board
    void initTextureBoard();
    void initSpriteBoard();
    sf::Texture textureBoard;
    sf::Sprite spriteBoard;

    // Graphic
    bool isTransform;
    bool isRender;
    bool isMove;
    Point start;
    Point end;

    PieceTray killedWhitePiece;
    PieceTray killedBlackPiece;

    // Square direction
    sf::CircleShape squareDirection;
    sf::CircleShape squareDirectionKill;
    vector<sf::CircleShape> squareDirections;

    // Sound effect
    sf::Sound choosePieceSound;
    sf::SoundBuffer choosePieceSound_buffer;
    sf::Sound movePieceSound;
    sf::SoundBuffer movePS_buffer;
    sf::Sound killOtherPieceSound;
    sf::SoundBuffer killOtherPieceSound_buffer;
    sf::Sound winGameSound;
    sf::SoundBuffer winGameSound_buffer;
    sf::Sound beInCheckSound;
    sf::SoundBuffer beInCheckSound_buffer;

    int soundEffectVolume;


public:
    Board();
    ~Board();

    // game logic
    void initBoard(int a[8][8], int _turn,int _win);
    bool canMoveInBoard(vector<Point> listValidMoves, Point end);
    vector<Point> canMove(Point start);
    bool endGame();
    void clearBoard();
    Piece *&Get(Point a);
    bool saveGame();
    bool loadGame();
    bool checkmate(int color);
    vector<Point> canLosePiece(int color);
    void Undo();
    void Redo();
    int getTurn();

    // Draw board
    void renderBoard(sf::RenderTarget &target);

    // Graphics
    void transformPawn(sf::Vector2f mousePosView);
    void savePointStart(sf::Vector2f mousePosView);
    Point getPositionPiece(sf::Vector2f mousePosView);
    void Move(sf::Vector2f mousePosView);
    void updateMove(sf::Vector2f mousePosView);

    // square Direction
    void initSquareDirection();
    void createSquareDirections(vector<Point> listValidMoves);
    void renderSquareDirecitons(sf::RenderTarget &target);

    // Sound effect
    void initSound();
    void setSoundEffectVolume(int volume);
    
    // machine
    void MoveMachine();
    void Find(Point &start, Point &end);
    Point Chose(vector<Point> list,int vector);
};
