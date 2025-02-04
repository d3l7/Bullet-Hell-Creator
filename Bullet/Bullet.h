#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>

using namespace sf;

class Bullet
{
private:
    //Attributes
    RectangleShape hitbox;

    float timeToFire;  //Unique to bullets since we want to fire them in sequence
    float size;

    Vector2f movementSpeed;
    Vector2f startSpeed;
    float speedMultiplier;

    bool destroyOnImpact;
    bool destroyOnLeavingScreen;
    bool fireOnSpawn;


    //Private Methods
    void init_attributes();
    void init_hitbox();

public:
    //Constructors / Destructors
    Bullet(Vector2f movement_speed);
    virtual ~Bullet();

    //Accessors
    const float get_size() const;
    const Vector2f get_speed() const;
    const FloatRect get_bounds() const;
    const bool outside_window(const float bound_x, const float bound_y) const;
    const bool impact_destruction() const;

    //Methods
    void set_speed(const Vector2f speed);
    void set_fire_time(const int time);

    void fire_bullet();
    void turn_to_target(const float obj_centre_x, const float objcentre_y);

    void update();
    void render(RenderTarget& target);
};
