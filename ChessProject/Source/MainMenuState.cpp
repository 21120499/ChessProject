#include <SFML/Window/Event.hpp>
#include <iostream>
#include "GameManager.h"
#include "WindowState.hpp"

MainMenuState::MainMenuState()
{
}

void MainMenuState::pollEvents(GameManager *gameMan)
{
    sf::Event ev;
    while (gameMan->getRenderWindow().pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            gameMan->getRenderWindow().close();
        }
        else if (ev.type == sf::Event::MouseButtonPressed)
        {
            switch (this->currentChoice)
            {
            case 0:
                std::cout << "Resume" << std::endl;
                gameMan->getSelectionSound().play();
                gameMan->clearScreen();
                gameMan->setState(gameMan->getGameState());
                break;

            case 1:
                std::cout << "New game" << std::endl;
                gameMan->getSelectionSound().play();
                if (gameMan->hasGameInProgress && !gameMan->getGameState()->endGame()) {
                    gameMan->showSaveGamePopup2 = true;
                }else {
                    gameMan->showPlayModePopup = true;
                }
                break;
                
            case 2:
                std::cout << "Load game" << std::endl;
                gameMan->getSelectionSound().play();
                if (!gameMan->hasGameInProgress) {
                    gameMan->initGameState();
                }
                gameMan->getGameState()->loadGame();
                gameMan->getGameState()->resetGameState();
                gameMan->hasGameInProgress = true;
                gameMan->setState(gameMan->getGameState());
                break;
                
            case 3:
                std::cout << "Setting" << std::endl;
                gameMan->getSelectionSound().play();
                gameMan->clearScreen();
                gameMan->setState(gameMan->getSettingState());
                return;
            case 4:
                std::cout << "Exit" << std::endl;
                gameMan->getSelectionSound().play();
                exit(2);
                break;
            default:
                break;
            }
        }
    }

    // live mouse
    int i = gameMan->hasGameInProgress ? 0 : 1;
    for (; i < this->numberOfButtons; ++i)
    {
        if (button[i].isMouseOver(gameMan->getRenderWindow()))
        {
            currentChoice = i;
            update(gameMan);
            break;
        }
        currentChoice = -1;
    }
}

void MainMenuState::init(GameManager *gameMan)
{

    // Load sound effect
    sf::SoundBuffer soundBuffer;
    if (!this->soundBuffer.loadFromFile("Asset/selectionSound.wav"))
    {
        std::cout << "Can not load file sound effect in class MainMenu" << std::endl;
    }
    else
    {
        gameMan->getSelectionSound().setBuffer(this->soundBuffer);
    }

    // Game title
    if (!this->font.loadFromFile("Asset/Pacifico.ttf"))
    {
    }
    this->background.setSize(sf::Vector2f(gameMan->getRenderWindow().getSize().x,
                                          gameMan->getRenderWindow().getSize().y));
    this->bg_texture.loadFromFile("Asset/bg_image.jpg");
    this->background.setTexture(&this->bg_texture);

    this->gameTitle.setString("Chess Game");
    this->gameTitle.setCharacterSize(32);
    this->gameTitle.setFont(this->font);
    this->gameTitle.setFillColor(sf::Color::Magenta);
    this->gameTitle.setOrigin(this->gameTitle.getLocalBounds().width / 2,
                              this->gameTitle.getLocalBounds().height / 2);
    this->gameTitle.setPosition(gameMan->getRenderWindow().getSize().x / 2,
                                gameMan->getRenderWindow().getSize().y / 2 - 200);

    // Option buttons
    this->currentChoice = 0;
    button[0].setTitle("Resume");
    button[1].setTitle("New game");
    button[2].setTitle("Load game");
    button[3].setTitle("Setting");
    button[4].setTitle("Exit");

    this->numberOfButtons = 5;
    for (int i = 0; i < numberOfButtons; ++i)
    {
        button[i].setSize(150, 30);
        button[i].setBackgroundColor(sf::Color(0, 0, 0, 0));
        button[i].setTextColor(sf::Color::White);
        button[i].setFont(this->font);
        button[i].setTextSize(28);
        button[i].setPosition(gameMan->getRenderWindow().getSize().x / 2,
                              gameMan->getRenderWindow().getSize().y / 2 - 60 + 45 * i);
    }

}

void MainMenuState::draw(GameManager *gameMan)
{
    gameMan->getRenderWindow().draw(this->background);
    gameMan->getRenderWindow().draw(this->gameTitle);

    int i = gameMan->hasGameInProgress ? 0 : 1;
    for (; i < this->numberOfButtons; ++i)
    {
        button[i].drawTo(gameMan->getRenderWindow());
    }
}

void MainMenuState::update(GameManager *gameMan)
{
    int i = gameMan->hasGameInProgress ? 0 : 1;
    for (; i < this->numberOfButtons; ++i)
    {
        button[i].setTextSize(20);
        button[i].setTextColor(sf::Color::White);
        button[i].setOriginToCenterForText();
        if (i == currentChoice)
        {
            button[i].setTextSize(25);
            button[i].setTextColor(sf::Color::Green);
            button[i].setOriginToCenterForText();
        }
    }

}




