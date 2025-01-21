#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

using namespace sf;

class Bullet
{
private:
    //Attributes
    RectangleShape hitbox;

    float size;
    float movementSpeed;
    bool destroyOnImpact;

    //Private Methods
    void init_attributes();
    void init_hitbox();

public:
    //Constructors / Destructors
    Bullet();
    ~Bullet();

    //Accessors
    const float getX() const;
    const float getY() const;
    const float getSize() const;
    const float getSpeed() const;
    

    //Methods
    void move(const float dirX, const float dirY);

    void update();
    void render(RenderTarget& target);
};
