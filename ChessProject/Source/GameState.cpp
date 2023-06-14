#include "WindowState.hpp"
#include "PieceFactory.h"
#include "GameManager.h"

// Object
void GameState::initBoard()
{
    this->board = new Board;
}

// font
void GameState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/VHEXOTIC.TTF"))
    {
        std::cout << "ERROR::GameState::INITFONTS::Failed to load font!"
                  << endl;
    }

    if (!this->fontWinGame.loadFromFile("Fonts/VNBODO.TTF"))
    {
        std::cout << "ERROR::GameState::INITFONTS::Failed to load font!"
                  << endl;
    }
}

// text
void GameState::initText()
{
    // text win
    this->uiText.setFont(this->fontWinGame);
    this->uiText.setCharacterSize(99);

    // text replay
    this->uiTextReplay.setFont(this->fontWinGame);
    this->uiTextReplay.setCharacterSize(35);

    // text check mate
    this->uiTextCheckMate.setFont(this->font);
    this->uiTextCheckMate.setCharacterSize(35);

    // replaying
    this->uiTextReplaying.setFont(this->font);
    this->uiTextReplaying.setCharacterSize(32);
}

// Contructor, Destructor
void GameState::init(GameManager *gameMan)
{
    this->isEndGame = false;
    this->isReplay = false;
    this->isRenderWinText = false;
    this->isRenderCheckMate = false;
    this->isRenderReplaying = false;
    this->initBoard();
    this->initFonts();
    this->initText();

    // ### Quoc
    this->initButton();
    this->initMenuPicture(gameMan);
    // ###
}

GameState::~GameState()
{
    delete this->board;
}

// Accessors
bool GameState::running(GameManager *gameMan)
{
    return gameMan->getRenderWindow().isOpen();
}

// Functions
void GameState::pollEvents(GameManager *gameMan)
{
    sf::Event ev;
    while (gameMan->getRenderWindow().pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
            gameMan->getRenderWindow().close();

        if (this->isEndGame == false)
        {
            if (this->board->type == 0) // che do choi voi nguoi
            {
                switch (ev.type)
                {
                case sf::Event::MouseButtonPressed:

                    // poll for pieces
                    if (this->board->isTransform == true)
                    {
                        this->board->transformPawn(this->mousePosView);
                    }
                    else
                    {
                        this->board->savePointStart(this->mousePosView);
                    }

                    // poll ev for button
                    if (this->homeBtn.isMouseOver(gameMan->getRenderWindow()))
                    {
                        gameMan->showBackMenuPopup = true;
                    }

                    if (this->saveGameBtn.isMouseOver(gameMan->getRenderWindow()))
                    {
                        gameMan->showSaveGamePopup = true;
                    }

                    if (this->undoBtn.isMouseOver(gameMan->getRenderWindow()))
                    {
                        this->board->Undo();
                    }

                    if (this->redoBtn.isMouseOver(gameMan->getRenderWindow()))
                    {
                        this->board->Redo();
                    }

                    break;
                case sf::Event::MouseButtonReleased:
                    this->board->Move(this->mousePosView);
                    break;
                default:
                    break;
                }
            }
            else // che do choi voi may
            {
                if (this->board->turn == 1)
                {
                    switch (ev.type)
                    {
                    case sf::Event::MouseButtonPressed:

                        // poll for pieces
                        if (this->board->isTransform == true)
                        {
                            this->board->transformPawn(this->mousePosView);
                        }
                        else
                        {
                            this->board->savePointStart(this->mousePosView);
                        }

                        // poll ev for button
                        if (this->homeBtn.isMouseOver(gameMan->getRenderWindow()))
                        {
                            gameMan->showBackMenuPopup = true;
                        }

                        if (this->saveGameBtn.isMouseOver(gameMan->getRenderWindow()))
                        {
                            gameMan->showSaveGamePopup = true;
                        }

                        if (this->undoBtn.isMouseOver(gameMan->getRenderWindow()))
                        {
                            this->board->Undo();
                            this->board->Undo();
                        }

                        if (this->redoBtn.isMouseOver(gameMan->getRenderWindow()))
                        {
                            this->board->Redo();
                            this->board->Redo();
                        }

                        break;

                    case sf::Event::MouseButtonReleased:
                        this->board->Move(this->mousePosView);
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    this->board->MoveMachine();
                }
            }
            this->board->updateMove(this->mousePosView);
            this->updateCheckMateText();
        }
        else
        {
            this->isRenderCheckMate = false;
            this->updateWinText();
            switch (ev.type)
            {
            case sf::Event::MouseButtonPressed:
                if (this->undoBtn.isMouseOver(gameMan->getRenderWindow()) && this->isReplay == false)
                {
                    this->isReplay = true;
                    this->isRenderWinText = false;
                    this->isRenderReplaying = true;
                    this->updateReplaying();
                    while (this->board->beforeMoves.size() > 0)
                    {
                        this->board->Undo();
                    }
                }
                // live mouse
                if (this->undoBtn.isMouseOver(gameMan->getRenderWindow()) && this->isReplay)
                {
                    this->board->Undo();
                }

                if (this->redoBtn.isMouseOver(gameMan->getRenderWindow()) && this->isReplay)
                {
                    this->board->Redo();
                }

                if (this->homeBtn.isMouseOver(gameMan->getRenderWindow()))
                {
                    gameMan->showBackMenuPopup = true;
                }
                break;
            }
        }
    }
}

void GameState::updateMousePosition(sf::RenderWindow &window)
{
    this->mousePosWindow = sf::Mouse::getPosition(window);
    this->mousePosView = window.mapPixelToCoords(this->mousePosWindow);
    // cout << this->mousePosView.x << " " << this->mousePosView.y << endl;
}

void GameState::updateEndGame()
{
    // neu isEndGame la true thi se luon cho no la true
    if (this->isEndGame == false)
        this->isEndGame = this->board->endGame();
}

void GameState::updateWinText()
{
    if (this->isReplay == false)
    {
        this->isRenderReplaying = false;
        this->isRenderWinText = true;
    }
    if (this->board->win == 1)
    {
        this->uiText.setString("White Win");
        this->uiText.setFillColor(sf::Color(249, 212, 26, 255));
    }
    else if (this->board->win == -1)
    {
        this->uiText.setString("Black Win");
        this->uiText.setFillColor(sf::Color(249, 212, 26, 255));
    }
    else if (this->board->win == 0)
    {
        this->uiText.setString("Draw");
        this->uiText.setFillColor(sf::Color(249, 212, 26, 255));
    }
    this->uiText.setOrigin(this->uiText.getLocalBounds().width / 2, this->uiText.getLocalBounds().height / 2);
    this->uiText.setPosition(400, 330);

    // text replay
    this->uiTextReplay.setString("Click Undo to replay");
    this->uiTextReplay.setFillColor(sf::Color(245, 146, 33, 255));
    this->uiTextReplay.setOrigin(this->uiTextReplay.getLocalBounds().width / 2, this->uiTextReplay.getLocalBounds().height / 2);
    this->uiTextReplay.setPosition(400, 415);
}

void GameState::updateCheckMateText()
{
    if (this->board->checkmate(this->board->turn))
    {
        this->isRenderCheckMate = true;
        this->uiTextCheckMate.setString("Check\n mate");
        this->uiTextCheckMate.setFillColor(sf::Color::Red);
        this->uiTextCheckMate.setOrigin(this->uiTextCheckMate.getLocalBounds().width / 2, this->uiTextCheckMate.getLocalBounds().height / 2);
        this->uiTextCheckMate.setPosition(1115, 175);
    }
    else
    {
        this->isRenderCheckMate = false;
    }
}

void GameState::updateReplaying()
{
    this->uiTextReplaying.setString("Replay...");
    this->uiTextReplaying.setFillColor(sf::Color::Red);
    this->uiTextReplaying.setOrigin(this->uiTextReplaying.getLocalBounds().width / 2, this->uiTextReplaying.getLocalBounds().height / 2);
    this->uiTextReplaying.setPosition(1120, 160);
}

void GameState::update(GameManager *gameMan)
{
    this->updateMousePosition(gameMan->getRenderWindow());

    this->updateEndGame();

    if (this->board->getTurn() == 1)
    {
        this->turnImage.setTexture(&this->whiteTurnTexture);
    }
    else
    {
        this->turnImage.setTexture(&this->blackTurnTexture);
    }

    // animation for buttons
    if (this->homeBtn.isMouseOver(gameMan->getRenderWindow()))
    {
        this->homeBtn.setScale(1.5, 1.5);
        this->homeBtn.setOriginToCenter();
    }
    else
    {
        this->homeBtn.setScale(1, 1);
        homeBtn.setOriginToCenter();
    }

    if (this->saveGameBtn.isMouseOver(gameMan->getRenderWindow()))
    {
        this->saveGameBtn.setScale(1.5, 1.5);
        saveGameBtn.setOriginToCenter();
    }
    else
    {
        this->saveGameBtn.setScale(1, 1);
        saveGameBtn.setOriginToCenter();
    }

    if (this->undoBtn.isMouseOver(gameMan->getRenderWindow()))
    {
        this->undoBtn.setScale(1.5, 1.5);
        ;
        undoBtn.setOriginToCenter();
    }
    else
    {
        this->undoBtn.setScale(1, 1);
        undoBtn.setOriginToCenter();
    }

    if (this->redoBtn.isMouseOver(gameMan->getRenderWindow()))
    {
        this->redoBtn.setScale(1.5, 1.5);
        redoBtn.setOriginToCenter();
    }
    else
    {
        this->redoBtn.setScale(1, 1);
        redoBtn.setOriginToCenter();
    }

    // update sound effect volume
    this->board->setSoundEffectVolume(gameMan->getSoundEffectVolume());
}

void GameState::renderText(sf::RenderTarget &target)
{
    target.draw(this->uiText);
    target.draw(this->uiTextReplay);
}

void GameState::renderCheckMateText(sf::RenderTarget &target)
{
    target.draw(this->uiTextCheckMate);
}

void GameState::renderReplaying(sf::RenderTarget &target)
{
    target.draw(this->uiTextReplaying);
}

void GameState::draw(GameManager *gameMan)
{
    gameMan->getRenderWindow().draw(this->backgroundInGame);

    this->board->renderBoard(gameMan->getRenderWindow());

    // Draw square direction
    this->board->renderSquareDirecitons(gameMan->getRenderWindow());

    // render text
    if (this->isRenderWinText)
        this->renderText(gameMan->getRenderWindow());

    // render text check mate
    if (this->isRenderCheckMate)
        this->renderCheckMateText(gameMan->getRenderWindow());

    if (this->isRenderReplaying)
        this->renderReplaying(gameMan->getRenderWindow());

    // Draw buttons
    homeBtn.drawTo(gameMan->getRenderWindow());
    saveGameBtn.drawTo(gameMan->getRenderWindow());
    undoBtn.drawTo(gameMan->getRenderWindow());
    redoBtn.drawTo(gameMan->getRenderWindow());

    gameMan->getRenderWindow().draw(this->turnImage);
}

void GameState::initButton()
{
    // setting basic infor for buttons
    homeBtn.setSize(32, 32);
    saveGameBtn.setSize(32, 32);
    undoBtn.setSize(32, 32);
    redoBtn.setSize(32, 32);

    //  - set position
    int halfOfLocalBounds = 16; // 32/2 : 'cause the buttons all have the same size
    homeBtn.setPosition(1140 + halfOfLocalBounds, 20 + halfOfLocalBounds);
    saveGameBtn.setPosition(1060 + halfOfLocalBounds, 20 + halfOfLocalBounds);
    undoBtn.setPosition(1060 + halfOfLocalBounds, 430 + halfOfLocalBounds);
    redoBtn.setPosition(1140 + halfOfLocalBounds, 430 + halfOfLocalBounds);

    // init and set texture for buttons
    if (!homeBtnTexture.loadFromFile("Picture/home-page.png"))
    {
        std::cout << "Load texture for home button fail" << std::endl;
    }
    else
    {
        homeBtn.setTexture(this->homeBtnTexture);
    }

    if (!saveGameBtnTexture.loadFromFile("Picture/save-file.png"))
    {
        std::cout << "Load texture for save game button fail" << std::endl;
    }
    else
    {
        saveGameBtn.setTexture(this->saveGameBtnTexture);
    }

    if (!undoBtnTexture.loadFromFile("Picture/undo.png"))
    {
        std::cout << "Load texture for home button fail" << std::endl;
    }
    else
    {
        undoBtn.setTexture(this->undoBtnTexture);
    }

    if (!redoBtnTexture.loadFromFile("Picture/redo.png"))
    {
        std::cout << "Load texture for home button fail" << std::endl;
    }
    else
    {
        redoBtn.setTexture(this->redoBtnTexture);
    }
}

void GameState::initMenuPicture(GameManager *gameMan)
{
    // load and set turn image
    turnImage.setSize({120, 120});
    turnImage.setPosition(1055, 280);
    if (!blackTurnTexture.loadFromFile("Picture/blackTurn.png") ||
        !whiteTurnTexture.loadFromFile("Picture/whiteTurn.png"))
    {
        std::cout << "Fail to load turn image texture" << std::endl;
    }
    else
    {
        turnImage.setTexture(&this->whiteTurnTexture);
    }

    // background: last load, first draw :v
    backgroundInGame.setSize({(float)gameMan->getRenderWindow().getSize().x,
                              (float)gameMan->getRenderWindow().getSize().y});
    if (!bgInGameTexture.loadFromFile("Picture/inGame_bg.jpg"))
    {
        std::cout << "Cannot load background in game" << std::endl;
    }
    else
    {
        backgroundInGame.setTexture(&bgInGameTexture);
    }
}

void GameState::saveGame()
{
    this->board->saveGame();
}

void GameState::loadGame()
{
    this->board->loadGame();
}

void GameState::setBoardType(int type = 1)
{
    this->board->type = type;
}

void GameState::resetGameState()
{
    this->isRenderReplaying = false;
    this->isEndGame = false;
    this->isReplay = false;
    this->isRenderWinText = false;
    this->isRenderCheckMate = false;
}

bool GameState::endGame() {
    return this->isEndGame;
}



