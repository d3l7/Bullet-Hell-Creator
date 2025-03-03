#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <iostream>

using namespace sf;

/*
    Class to initialise everything to do with the player
    - Declares and initialises player attributes
    - Provides accessors for appropriate player attributes
    - Provides movement capability within refernce to the player hitbox relative to the window
*/

class Player
{
private:
    //Attributes
    int health;

    RectangleShape hitbox;
    float movementSpeed;
    float size;

    //Private Methods
    void init_attributes();
    void init_hitbox();

public:
    //Constructors / Destructors
    Player();
    ~Player();

    //Getters
    const int get_health() const;
    const float get_size() const;
    const Vector2f& get_pos() const;
    const FloatRect get_bounds() const;
    const float get_speed() const;

    //Setters
    void set_health(const int health_change);
    void set_size(const float new_size);
    void set_speed(const float new_speed);
    
    //Methods
    void move(const float dirX, const float dirY);
    
    void update();
    void render(RenderTarget& target);
};