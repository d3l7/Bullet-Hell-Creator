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
    this->velocity.x = 0.f;  
    this->velocity.y = 0.f;

    //Temporary speed variables to update speed until we want to fire the bullet
    this->tempVelocity.x = 0.f;
    this->tempVelocity.y = 0.f;
}

void Bullet::init_hitbox()
{
    this->hitbox.setSize(Vector2f(this->size, this->size));
    this->hitbox.setFillColor(Color::Red);
}

//Constructors / Destructors
Bullet::Bullet()
{
    this->init_attributes();
    this->init_hitbox();
}

Bullet::~Bullet()
{

}

//Accessors

//Getters
const float Bullet::get_size() const
{
    return this->size;
}

const Vector2f Bullet::get_speed() const
{
    return this->velocity;
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

//Setters
void Bullet::set_size(const float new_size)
{
    this->hitbox.setSize(Vector2f(new_size, new_size));
}

void Bullet::set_speed(const Vector2f new_speed)
{
    this->velocity.x = new_speed.x;
    this->velocity.y = new_speed.y;
}

void Bullet::set_fire_time(const int time)
{
    this->timeToFire = time;
}

void Bullet::set_pos(const float pos_x, const float pos_y)
{
    this->hitbox.setPosition(Vector2f(pos_x, pos_y));
}

// Public Methods
void Bullet::fire_bullet()
{
    this->set_speed(this->tempVelocity);
}

void Bullet::turn_to_target(const float obj_centre_x, const float obj_centre_y)
{
    Vector2f aimDir;
    Vector2f aimDirNorm;

    Vector2f objCentre = Vector2f(obj_centre_x, obj_centre_y);
    Vector2f bulletCentre = Vector2f((this->hitbox.getPosition().x + this->get_size()), (this->hitbox.getPosition().y + this->get_size()));
    aimDir = objCentre - bulletCentre;
    aimDirNorm = aimDir / static_cast<float>(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));  // Normalise the Vector

    this->tempVelocity = aimDirNorm;

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
    this->hitbox.move(this->velocity * this->speedMultiplier);
}

void Bullet::render(RenderTarget& target)
{
    target.draw(this->hitbox);
}
