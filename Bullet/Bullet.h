#pragma once

#include "SFML/Graphics.hpp"
#include <chrono>
#include <thread>


using namespace sf;

class Bullet
{
private:
    //Attributes
    RectangleShape hitbox;

    Vector2f direction;

    float timeToFire;  //Unique to bullets since we want to fire them in sequence
    float size;
    float movementSpeed;
    bool destroyOnImpact;
    bool destroyOnLeavingScreen;
    bool fireOnSpawn;
    float startSpeed;

    //Private Methods
    void init_attributes();
    void init_hitbox();

public:
    //Constructors / Destructors
    Bullet(float dir_x, float dir_y, float movement_speed);
    virtual ~Bullet();

    //Accessors
    const float get_size() const;
    const float get_speed() const;
    const FloatRect get_bounds() const;
    const bool outside_window(const float bound_x, const float bound_y) const;
    const bool impact_destruction() const;

    //Methods
    void set_speed(const float speed);
    void set_fire_time(const int time);

    void fire_bullet();

    void update();
    void render(RenderTarget& target);
};
