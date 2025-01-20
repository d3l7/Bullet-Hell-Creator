#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

using namespace sf;

class Player
{
private:
    //Attributes
    RectangleShape hitbox;
    float movementSpeed;
    float size;

    //Private Methods
    void init_hitbox();

public:
    //Constructors / Destructors
    Player();
    ~Player();

    //Accessors

    const float getX() const;
    const float getY() const;
    const float getSize() const;

    //Methods
    void move(const float dirX, const float dirY);
    
    void update();
    void render(RenderTarget& target);
};