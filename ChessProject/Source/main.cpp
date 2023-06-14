
#include "WindowState.hpp"
#include "GameManager.h"

int main()
{
    GameManager game;
    game.initWindow();
            
    while (game.isWindowOpen()) {
        // process state
        game.clearScreen();
        game.pollEvents();
        game.update();
        game.draw();
        game.getRenderWindow().display();
    } 
}