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

    Vector2f velocity;
    Vector2f tempVelocity;
    float speedMultiplier;

    bool destroyOnImpact;
    bool destroyOnLeavingScreen;
    bool fireOnSpawn;


    //Private Methods
    void init_attributes();
    void init_hitbox();

public:
    //Constructors / Destructors
    Bullet();
    virtual ~Bullet();

    //Accessors 
    
    //Getters
    const float get_size() const;
    const Vector2f get_speed() const;
    const FloatRect get_bounds() const;
    const bool outside_window(const float bound_x, const float bound_y) const;
    const bool impact_destruction() const;

    //Setters
    void set_size(const float new_size);
    void set_speed(const Vector2f new_speed);
    void set_fire_time(const int time);
    void set_pos(const float pos_x, const float pos_y);

    //Methods
    void fire_bullet();
    void turn_to_target(const float obj_centre_x, const float objcentre_y);

    void update();
    void render(RenderTarget& target);
};
