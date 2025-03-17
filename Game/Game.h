#pragma once

#include "../Player/Player.h"
#include "../BulletPattern/BulletPattern.h"
#include <string>

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
    std::vector<BulletPattern*> bulletSequence; //Holds the current bullet sequence

    //Player
    Player* player;  

    //Flags
    bool patternChanged;
    bool creating;
    bool testing;
    bool entered;  //Flag for user inputs during creation
    bool start;
    bool sequenceBeat;

    //Other attributes
    int patternDelay;
    int baseDelay;  //Standard delay between patterns, customizable

    //Pointers
    int currentPattern; 
    int currentBullet;

    int frameRate;

    //Private Methods
    void init_attributes();
    void init_window();
    void init_player();
    
    /*
        Many objects of these two custom classes will be initialised and both depend on each other
        Thus references of such objects must be passed as parameters in order to reduce risk of memory loss/crashes
    */
    void init_pattern();  
    void init_bullet(BulletPattern* pattern, const float size, const float speed, const int time, 
                     const float pos_x, const float pos_y, const float target_x, const float target_y);

public:
    //Constructors / Destructors
    Game();
    ~Game();

    //Accessors
    const bool running() const;
    const bool creating_pattern() const;
    const bool testing_pattern() const;

    //Methods
    void poll_events();
    
    //Creating
    void edit_bullet(Bullet* bullet);

    //Testing
    void move_player();
    void spawn_bullet(BulletPattern* pattern, Bullet* bullet, const float pos_x, const float pos_y);

    void update_player();
    void update_bullets(BulletPattern* pattern);

    //Final functions
    void create();
    void test();
    void render();

};
