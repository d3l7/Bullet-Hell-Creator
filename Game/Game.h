#pragma once

#include "../Player/Player.h"
#include "../BulletPattern/BulletPattern.h"
#include <cmath>

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
    std::vector<BulletPattern*> bulletSequence; //Holds the current bullet sequence (might make a class for this later, or will make a general queue custom data structure for both patterns and sequences)

    //Player
    Player* player;  

    //Other attributes
    int patternDelay;
    int baseDelay;
    int currentPattern;

    //Private Methods
    void init_attributes();
    void init_window();
    void init_player();
    
    /*
        Many objects of these two custom classes will be initialised and both depend on each other
        Thus references of such objects must be passed as parameters in order to reduce risk of memory loss/crashes
    */
    void init_pattern();  
    void init_bullet(BulletPattern* pattern, const float pos_x, const float pos_y);

public:
    //Constructors / Destructors
    Game();
    ~Game();

    //Accessors
    const bool running() const;
    const BulletPattern* access_pattern(int position) const;

    //Methods

    void poll_events();
    
    void move_player();
    void spawn_bullet(BulletPattern* pattern, Bullet* bullet, const float pos_x, const float pos_y);

    void update_player();
    void update_bullets(BulletPattern* pattern);
    void update_current_sequence();

    void update();
    void render();

};
