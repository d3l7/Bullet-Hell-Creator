#include "Bullet.h"
#include <iostream>

using namespace sf;

// Private Methods
void Bullet::init_attributes()
{
    this->size = 7.5f;
    this->destroyOnImpact = true;
    this->destroyOnLeavingScreen = true;
    this->fireOnSpawn = false;
    this->timeToFire = 60;
    this->movementSpeed = 0;  //Base speed is 0 since we want to check for fire time first
}

void Bullet::init_hitbox()
{
    this->hitbox.setPosition(0.f, 360.f);
    this->hitbox.setSize(Vector2f(this->size, this->size));
    this->hitbox.setFillColor(Color::Red);
}

//Constructors / Destructors
Bullet::Bullet(float dir_x, float dir_y, float movement_speed)
{
    this->direction.x = dir_x;
    this->direction.y = dir_y;
    this->startSpeed = movement_speed;

    this->init_attributes();
    this->init_hitbox();
}

Bullet::~Bullet()
{

}

//Accessors
const float Bullet::get_size() const
{
    return this->size;
}

const float Bullet::get_speed() const
{
    return this->movementSpeed;
}

const FloatRect Bullet::get_bounds() const
{
    return this->hitbox.getGlobalBounds();
}

const bool Bullet::outside_window(const float bound_x, const float bound_y) const
{
    if((this->get_bounds().top + this->get_bounds().height < 0.f)  //Top
        or (this->get_bounds().left + this->get_bounds().width < 0.f)  //Lefthand side
        or (this->get_bounds().top > bound_y)  //Bottom
        or (this->get_bounds().left > bound_x))  //Righthand side
    {
        return true;
    }else{
    return false;
    }
}

const bool Bullet::impact_destruction() const
{
    return this->destroyOnImpact;
}

// Public Methods
void Bullet::set_speed(const float new_speed)
{
    this->movementSpeed = new_speed;
}

void Bullet::set_fire_time(const int time)
{
    this->timeToFire = time;
}

void Bullet::fire_bullet()
{
    this->set_speed(this->startSpeed);
}

void Bullet::update()
{
    //Allow for bullet waiting time after spawn
    if(not this->fireOnSpawn and (this->timeToFire != 0.f))
    {
        --this->timeToFire;
        std::cout << this->timeToFire << std::endl;
    }else{
        this->fire_bullet();
    }
    //Move bullet
    this->hitbox.move(this->movementSpeed * this->direction);
}

void Bullet::render(RenderTarget& target)
{
    target.draw(this->hitbox);
}
