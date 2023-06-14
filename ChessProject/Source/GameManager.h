
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "WindowState.hpp"
#include "Popup.h"

class SettingState;
class MainMenu;
enum PlayMode
{
    PLAYER,
    BOT
};

class GameManager
{
private:
    // Video mode
    sf::RenderWindow window;

    sf::Image gameIcon;
    PlayMode playMode;

    // States
    WindowState *currentState;
    MainMenuState *menu;
    SettingState *setting;
    GameState *game;

    // Popups
    sf::Font popupFont;
    sf::Texture popupTexture;
    Popup saveGamePopup;
    Popup backMainMenuPopup;
    Popup saveGameToCreatANewOne;
    Popup chooseMode;

    // Music
    sf::Music bg_music;
    sf::SoundBuffer selectionSoundBuffer;
    sf::Sound selectionSound;

    // Volume
    int bg_musicVol;
    int soundEffectVol;

public:
    // signs to be used in states
    bool hasGameInProgress;
    bool showPlayModePopup;
    bool showSaveGamePopup;
    bool showSaveGamePopup2;
    bool showBackMenuPopup;
    // Graphics
    ~GameManager();
    void initWindow();
    bool isWindowOpen();
    void initGameState();
    void initMainMenuState();
    void initSettingState();
    // States
    void setState(WindowState *state);
    MainMenuState *getMenuState();
    SettingState *getSettingState();
    GameState *getGameState();
    WindowState *getCurrentState();
    sf::Sound &getSelectionSound();
    void drawCurrentState();
    // Window process
    void clearScreen();
    void pollEvents();
    void update();
    void draw();
    sf::RenderWindow &getRenderWindow();
    // Popups
    void initPopup();
    void pollPopUpEvent();
    void updatePopup();
    void drawPopup();
    // Music and sound
    void setBGMusicVol(int volume);
    void setSoundEffectVol(int volume);
    int getSoundEffectVolume();
};