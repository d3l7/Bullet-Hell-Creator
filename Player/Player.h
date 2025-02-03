#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <iostream>

using namespace sf;

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

    //Accessors
    const int get_health() const;
    const float get_size() const;
    const Vector2f& get_pos() const;
    const FloatRect get_bounds() const;

    //Methods
    void set_health(const int health_change);
    void move(const float dirX, const float dirY);
    
    void update();
    void render(RenderTarget& target);
};