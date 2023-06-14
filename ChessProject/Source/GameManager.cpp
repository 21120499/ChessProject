#include "GameManager.h"

GameManager::~GameManager()
{
    if (this->menu)
        delete this->menu;
    if (this->setting)
        delete this->setting;
    if (this->game)
        delete this->game;
}

void GameManager::initWindow()
{

    this->window.create(sf::VideoMode(1200, 800), "ChessGame", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(90);

    // Creat and load 2 states
    this->initMainMenuState();
    this->initSettingState();

    this->currentState = this->menu;

    // Load background music
    if (!this->bg_music.openFromFile("Asset/bg_music.ogg"))
    {
        std::cout << "Cannot load audio" << std::endl;
    }
    else
    {
        bg_musicVol = 50;
        bg_music.setVolume(50);
        bg_music.play();
        bg_music.setLoop(true);
    }
    this->soundEffectVol = 50;
    if(!this->gameIcon.loadFromFile("Asset/gameIcon.png")) {
        std::cout << "GameManager::initWindow() error" << std::endl;
    }else {
        this->window.setIcon(this->gameIcon.getSize().x, this->gameIcon.getSize().y, gameIcon.getPixelsPtr());
    }

    this->hasGameInProgress = false;

    // Popups
    this->initPopup();
    this->showBackMenuPopup = false;
    this->showPlayModePopup = false;
    this->showSaveGamePopup = false;
    this->showSaveGamePopup2 = false;
}

bool GameManager::isWindowOpen()
{
    return this->window.isOpen();
}

void GameManager::initGameState()
{
    this->game = new GameState;
    this->game->init(this);
}
void GameManager::initMainMenuState()
{
    this->menu = new MainMenuState;
    this->menu->init(this);
}
void GameManager::initSettingState()
{
    this->setting = new SettingState;
    this->setting->init(this);
}

void GameManager::initPopup()
{
    if (!this->popupTexture.loadFromFile("Asset/popupImage.png") ) {
        std::cout << "GameManager::initPopup() fail to load popup texture";
    }

    if (!this->popupFont.loadFromFile("Asset/Pacifico.ttf"))
    {
        std::cout << "Fail to load popup font" << std::endl;
    }

    // choose mode play game
    this->chooseMode.setFrameSize({600, 300});
    this->chooseMode.setPosition(window.getSize().x / 2 - this->chooseMode.getSizeFrame().x / 2,
                                 window.getSize().y / 2 - this->chooseMode.getSizeFrame().y / 2);
    this->chooseMode.setNumberOfChoice(3);
    this->chooseMode.setFont(this->popupFont);
    this->chooseMode.setBackground(this->popupTexture);
    this->chooseMode.setTextSize(20);
    this->chooseMode.setTextColor(sf::Color::White);
    this->chooseMode.setTitle("Play With");
    this->chooseMode.setChoiceButtonSize(60, 30);
    this->chooseMode.setChoiceString("Player", 0);
    this->chooseMode.setChoiceString("Bot", 1);
    this->chooseMode.setChoiceString("Back", 2);

    // back Main Menu popup
    this->backMainMenuPopup.setFrameSize({600, 300});
    this->backMainMenuPopup.setPosition(window.getSize().x / 2 - this->backMainMenuPopup.getSizeFrame().x / 2,
                                        window.getSize().y / 2 - this->backMainMenuPopup.getSizeFrame().y / 2);
    this->backMainMenuPopup.setNumberOfChoice(2);
    this->backMainMenuPopup.setFont(this->popupFont);
    this->backMainMenuPopup.setBackground(this->popupTexture);
    this->backMainMenuPopup.setTextSize(20);
    this->backMainMenuPopup.setTextColor(sf::Color::White);
    this->backMainMenuPopup.setTitle("Menu");
    this->backMainMenuPopup.setContent("Do you wanna return to main menu?");
    this->backMainMenuPopup.setChoiceButtonSize(60, 30);
    this->backMainMenuPopup.setChoiceString("Yes", 0);
    this->backMainMenuPopup.setChoiceString("No", 1);

    // save game popup
    this->saveGamePopup.setFrameSize({600, 300});
    this->saveGamePopup.setPosition(window.getSize().x / 2 - this->saveGamePopup.getSizeFrame().x / 2,
                                    window.getSize().y / 2 - this->saveGamePopup.getSizeFrame().y / 2);
    this->saveGamePopup.setNumberOfChoice(2);
    this->saveGamePopup.setFont(this->popupFont);
    this->saveGamePopup.setBackground(this->popupTexture);
    this->saveGamePopup.setTextSize(20);
    this->saveGamePopup.setTextColor(sf::Color::White);
    this->saveGamePopup.setTitle("Save");
    this->saveGamePopup.setContent("Would you like to save the current game?");
    this->saveGamePopup.setChoiceButtonSize(60, 30);
    this->saveGamePopup.setChoiceString("Yes", 0);
    this->saveGamePopup.setChoiceString("No", 1);

    // save game when start a new one
    this->saveGameToCreatANewOne.setFrameSize({600, 300});
    this->saveGameToCreatANewOne.setPosition(window.getSize().x / 2 - this->saveGameToCreatANewOne.getSizeFrame().x / 2,
                                             window.getSize().y / 2 - this->saveGameToCreatANewOne.getSizeFrame().y / 2);
    this->saveGameToCreatANewOne.setNumberOfChoice(3);
    this->saveGameToCreatANewOne.setFont(this->popupFont);
    this->saveGameToCreatANewOne.setBackground(this->popupTexture);
    this->saveGameToCreatANewOne.setTextSize(20);
    this->saveGameToCreatANewOne.setTextColor(sf::Color::White);
    this->saveGameToCreatANewOne.setTitle("Save");
    this->saveGameToCreatANewOne.setContent("Would you like to save the current game \nbefore start a new one?");
    this->saveGameToCreatANewOne.setChoiceButtonSize(60, 30);
    this->saveGameToCreatANewOne.setChoiceString("Yes", 0);
    this->saveGameToCreatANewOne.setChoiceString("No", 1);
    this->saveGameToCreatANewOne.setChoiceString("Cancel", 2);
}

void GameManager::setState(WindowState *state)
{
    this->currentState = state;
}


MainMenuState *GameManager::getMenuState()
{
    return this->menu;
}

SettingState *GameManager::getSettingState()
{
    return this->setting;
}

GameState *GameManager::getGameState()
{
    return this->game;
}

WindowState *GameManager::getCurrentState()
{
    return this->currentState;
}

sf::Sound &GameManager::getSelectionSound()
{
    return this->selectionSound;
}

void GameManager::clearScreen()
{
    this->window.clear();
}

void GameManager::drawCurrentState()
{
    // this->windowState->pollEvents(this); ??
    this->currentState->draw(this);
}

sf::RenderWindow &GameManager::getRenderWindow()
{
    return this->window;
}

void GameManager::setBGMusicVol(int volume)
{
    this->bg_musicVol = volume;
    this->bg_music.setVolume(volume);
}

void GameManager::setSoundEffectVol(int volume)
{
    this->soundEffectVol = volume;
    this->selectionSound.setVolume(volume);
}

int GameManager::getSoundEffectVolume()
{
    return this->soundEffectVol;
}

void GameManager::drawPopup()
{
    if (this->showPlayModePopup)
        this->chooseMode.drawTo(this->window);

    if (this->showBackMenuPopup)
        this->backMainMenuPopup.drawTo(this->window);

    if (this->showSaveGamePopup)
        this->saveGamePopup.drawTo(this->window);

    if (this->showSaveGamePopup2)
        this->saveGameToCreatANewOne.drawTo(this->window);
}

void GameManager::pollEvents()
{

    // check this to block State's pollEvents when one of
    // these popups is being shown
    if (this->showBackMenuPopup | this->showPlayModePopup |
        this->showSaveGamePopup | this->showSaveGamePopup2)
    {
        this->pollPopUpEvent();
    }
    else
    {
        this->currentState->pollEvents(this);
    }
}

void GameManager::update()
{
    if (this->showBackMenuPopup | this->showPlayModePopup |
        this->showSaveGamePopup | this->showSaveGamePopup2)
    {
        this->updatePopup();
    }
    else
    {
        this->currentState->update(this);
    }
}

void GameManager::updatePopup() {
    if (this->showBackMenuPopup) {
        for (int i = 0; i < this->backMainMenuPopup.choices.size(); ++i) {
            if (backMainMenuPopup.choices[i].isMouseOver(this->window)) {
                backMainMenuPopup.choices[i].setBackgroundColor(sf::Color(238, 130, 238, 200));
            }
            else {
                backMainMenuPopup.choices[i].setBackgroundColor(sf::Color(238, 130, 238, 100));
            }
        }
    }else if (this->showPlayModePopup) {
        for (int i = 0; i < this->chooseMode.choices.size(); ++i) {
            if (chooseMode.choices[i].isMouseOver(this->window)) {
                chooseMode.choices[i].setBackgroundColor(sf::Color(238, 130, 238, 200));
            }
            else {
                chooseMode.choices[i].setBackgroundColor(sf::Color(238, 130, 238, 100));
            }
        }
    }
    else if (this->showSaveGamePopup) {
        for (int i = 0; i < this->saveGamePopup.choices.size(); ++i) {
            if (saveGamePopup.choices[i].isMouseOver(this->window)) {
                saveGamePopup.choices[i].setBackgroundColor(sf::Color(238, 130, 238, 200));
            }
            else {
                saveGamePopup.choices[i].setBackgroundColor(sf::Color(238, 130, 238, 100));
            }
        }
    }else {
        for (int i = 0; i < this->saveGameToCreatANewOne.choices.size(); ++i) {
            if (saveGameToCreatANewOne.choices[i].isMouseOver(this->window)) {
                saveGameToCreatANewOne.choices[i].setBackgroundColor(sf::Color(238, 130, 238, 200));
            }
            else {
                saveGameToCreatANewOne.choices[i].setBackgroundColor(sf::Color(238, 130, 238, 100));
            }
        }
    }

}

void GameManager::draw()
{
    this->drawCurrentState();
    this->drawPopup();
}

void GameManager::pollPopUpEvent()
{
    sf::Event ev;
    while (this->window.pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            this->window.close();
            break;

        case sf::Event::MouseButtonPressed:
            if (this->showPlayModePopup)
            {
                // Play with other player
                if (chooseMode.choices[0].isMouseOver(this->window))
                {
                    this->selectionSound.play();
                    this->playMode = PLAYER;
                    if (this->hasGameInProgress)
                        delete this->game;

                    this->initGameState();
                    this->game->setBoardType(0);
                    this->currentState = this->game; // set State
                    this->hasGameInProgress = true;
                    this->showPlayModePopup = false;
                }

                // Play with bot
                if (chooseMode.choices[1].isMouseOver(this->window)) {
                    this->selectionSound.play();
                    this->playMode = BOT;
                    if (this->hasGameInProgress)
                        delete this->game;

                    this->initGameState();
                    this->game->setBoardType(1);
                    this->currentState = this->game; // set State
                    this->hasGameInProgress = true;
                    this->showPlayModePopup = false;
                }

                // Cancel
                if (chooseMode.choices[2].isMouseOver(this->window)) {
                    this->selectionSound.play();
                    this->showPlayModePopup = false; // hide popup
                }
            }
            else if (this->showBackMenuPopup)
            {
                if (backMainMenuPopup.choices[0].isMouseOver(this->window)) {
                    this->selectionSound.play();
                    this->currentState = this->menu; // change state
                    this->showBackMenuPopup = false; // hide the popup
                }
                if (backMainMenuPopup.choices[1].isMouseOver(this->window)){
                    this->selectionSound.play();
                    this->showBackMenuPopup = false;
                }
            }
            else if (this->showSaveGamePopup)
            {
                if (saveGamePopup.choices[0].isMouseOver(this->window)) {
                    this->selectionSound.play();
                    this->game->saveGame();
                    this->showSaveGamePopup = false;
                }
                if (saveGamePopup.choices[1].isMouseOver(this->window)) {
                    this->selectionSound.play();
                    this->showSaveGamePopup = false;
                }
            }
            else if (this->showSaveGamePopup2)
            {
                // Yes
                if (saveGameToCreatANewOne.choices[0].isMouseOver(this->window)) {
                    this->selectionSound.play();
                    this->game->saveGame();
                    this->showSaveGamePopup2 = false;
                    this->showPlayModePopup = true;
                }
                
                // No
                if (saveGameToCreatANewOne.choices[1].isMouseOver(this->window)) {
                    this->selectionSound.play();
                    if (this->hasGameInProgress) {
                        delete this->game;
                    }
                    this->hasGameInProgress = false;
                    this->showPlayModePopup = true;
                    this->showSaveGamePopup2 = false; // hide popup
                }

                // Cancel
                if (saveGameToCreatANewOne.choices[2].isMouseOver(this->window)){
                    this->selectionSound.play();
                    this->showSaveGamePopup2 = false;
                }
            }
            break;
        }
    }
}
