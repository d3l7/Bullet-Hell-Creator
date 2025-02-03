#pragma once

#include "../Player/Player.h"
#include "../Bullet/Bullet.h"

using namespace sf;

/*
    Class that controls the game logic
    - Interaction between hitboxes
    - Implements the rendering of objects onto a window
    - Calls various methods and pulls together all the relevant classes in order to string them together 
*/

class Game
{
private:
    //Attributes
    
    //Window
    RenderWindow* window;
    VideoMode resolution;
    Event ev;

    //Resources
    std::vector<Bullet*> bullets;  //Holds the current bullet sequence

    //Bullet
    Bullet* bullet;

    //Player
    Player* player;  

    //Private Methods
    void init_attributes();
    void init_window();
    void init_player();
    void init_bullet();

public:
    //Constructors / Destructors
    Game();
    ~Game();

    //Accessors
    const bool running() const;

    //Methods

    void poll_events();
    
    void move_player();
    void spawn_bullet();

    void update_player();
    void update_bullets();
    void check_collision();

    void update();
    void render();

};
