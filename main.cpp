#include "Game\Game.h"

using namespace sf;

int main()
{
    //Initialise game engine
    Game game;

    //Game loop
    while(game.running())
    {
        game.poll_events();

        //Creating the pattern
        if (game.creating_pattern())
        {
            game.create();
        }

        //Game updates (when testing)
        if (game.testing_pattern())
        {
            game.test();
        }
        //Render
        game.render();
    }

    return 0;
}