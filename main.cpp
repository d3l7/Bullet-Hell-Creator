#include "Game\Game.h"

using namespace sf;

int main()
{
    //Initialise game engine
    Game game;

    //Game loop

    while(game.running())
    {
        //Update
        game.update();

        //Render
        game.render();
    }

    return 0;
}