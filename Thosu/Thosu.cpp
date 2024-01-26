#include <iostream>
#include "Game.h"

int main()
{
    Game game;

    while (game.isOpen()) {

        //Update, update the status logic
        game.update();
        
        //Render, visualizing updates
        game.render();
    }
}


