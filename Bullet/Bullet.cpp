#include "Bullet.h"

using namespace sf;

// Private Methods
void Bullet::init_attributes()
{
    this->size = 7.5f;
    
    this->destroyOnImpact = true;
    this->destroyOnLeavingScreen = true;
    
    this->fireOnSpawn = false;
    this->timeToFire = 240;
    this->speedMultiplier = 2.5f;

    //Base speed is 0 since we want to check for fire time first
    this->movementSpeed.x = 0.f;  
    this->movementSpeed.y = 0.f;
}

void Bullet::init_hitbox()
{
    this->hitbox.setPosition(0.f, 0.f);
    this->hitbox.setSize(Vector2f(this->size, this->size));
    this->hitbox.setFillColor(Color::Red);
}

//Constructors / Destructors
Bullet::Bullet(Vector2f movement_speed)
{
    this->startSpeed.x = movement_speed.x;
    this->startSpeed.y = movement_speed.y;

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

const Vector2f Bullet::get_speed() const
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
void Bullet::set_speed(const Vector2f new_speed)
{
    this->movementSpeed.x = new_speed.x;
    this->movementSpeed.y = new_speed.y;
}

void Bullet::set_fire_time(const int time)
{
    this->timeToFire = time;
}

void Bullet::fire_bullet()
{
    this->set_speed(this->startSpeed);
}

void Bullet::turn_to_target(const float obj_centre_x, const float obj_centre_y)
{
    Vector2f aimDir;
    Vector2f aimDirNorm;

    Vector2f objCentre = Vector2f(obj_centre_x, obj_centre_y);
    Vector2f bulletCentre = Vector2f((this->hitbox.getPosition().x + this->get_size()), (this->hitbox.getPosition().y + this->get_size()));
    aimDir = objCentre - bulletCentre;
    aimDirNorm = aimDir / static_cast<float>(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));  // Normalise the Vector

    this->set_speed(aimDirNorm);

}

void Bullet::update()
{
    //Allow for bullet waiting time after spawn
    if(not this->fireOnSpawn and (this->timeToFire != 0.f))
    {
        --this->timeToFire;
    }else{
        this->fire_bullet();
    }
    //Move bullet
    this->hitbox.move(this->movementSpeed * this->speedMultiplier);
}

void Bullet::render(RenderTarget& target)
{
    target.draw(this->hitbox);
}
