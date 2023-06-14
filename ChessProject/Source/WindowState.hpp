#pragma once
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio.hpp>
#include "Button.hpp"
#include "Board.h"

class GameManager;
class WindowState
{
public:
    virtual void init(GameManager *gameMan) = 0;
    virtual void pollEvents(GameManager *gameMan) = 0;
    virtual void update(GameManager *gameMan) = 0;
    virtual void draw(GameManager *gameMan) = 0;
};

class GameManager;

class MainMenuState : public WindowState
{
private:
    sf::RectangleShape background;
    sf::Texture bg_texture;
    sf::Font font;
    sf::Text gameTitle;
    int currentChoice;
    int numberOfButtons;
    Button button[5];

    // add sound effect
    sf::SoundBuffer soundBuffer;
    sf::Sound selectionSound;

public:
    void pollEvents(GameManager *gameMan);
    void update(GameManager *gameMan);
    void draw(GameManager *gameMan);
    void init(GameManager *gameMan);

    MainMenuState();
};

class SettingState : public WindowState
{
private:
    Button behindBar[2];
    Button frontBar[2];

    Button backButton;

    sf::Text bar1Title;
    sf::Text bar2Title;

    sf::Texture bg_texture;
    sf::RectangleShape background;

    sf::Font font;

    int changeMusicVol;
    int changeSoundVol;

public:
    SettingState();
    void init(GameManager *gameMan);
    void pollEvents(GameManager *gameMan);
    void update(GameManager *gameMan);
    void draw(GameManager *gameMan);

    // getter and setter
    int getBarMusicVolume();
    int getBarSoundVolume();
};

class GameState : public WindowState
{
private:
    // Mouse Position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // font
    sf::Font font;
    sf::Font fontWinGame;

    // Text
    sf::Text uiText;
    sf::Text uiTextCheckMate;
    sf::Text uiTextReplay;
    sf::Text uiTextReplaying;

    // object
    Board *board;
    bool isEndGame;
    bool isReplay;
    bool isRenderWinText;
    bool isRenderCheckMate;
    bool isRenderReplaying;

    // Private Functions
    void initFonts();
    void initText();
    void initBoard();

    // ### Quoc
    // buttons and their textures
    Button homeBtn;
    Button saveGameBtn;
    Button undoBtn;
    Button redoBtn;
    sf::Texture homeBtnTexture;
    sf::Texture saveGameBtnTexture;
    sf::Texture undoBtnTexture;
    sf::Texture redoBtnTexture;

    sf::RectangleShape turnImage;
    sf::Texture blackTurnTexture;
    sf::Texture whiteTurnTexture;

    // background
    sf::RectangleShape backgroundInGame;
    sf::Texture bgInGameTexture;
    // ###

public:
    // constructor, destructor
    ~GameState();

    // Accessors
    bool running(GameManager *gameMan);

    // Functions
    void updateEndGame();

    void updateWinText();
    void updateCheckMateText();
    void updateReplaying();
    void renderText(sf::RenderTarget &target);
    void renderCheckMateText(sf::RenderTarget &target);
    void renderReplaying(sf::RenderTarget &target);

    // ## Quoc
    // State processes
    void updateMousePosition(sf::RenderWindow &window);
    void pollEvents(GameManager *gameMan);
    void update(GameManager *gameMan);
    void draw(GameManager *gameMan);
    void init(GameManager *gameMan);

    // ulity functions;
    void initButton();
    void initMenuPicture(GameManager *gameMan);
    void saveGame();
    void loadGame();
    void setBoardType(int type);
    void resetGameState();
    bool endGame();
    // ##
};
