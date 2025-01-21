#include "Bullet.h"

using namespace sf;

// Private Methods
void Bullet::init_attributes()
{
    this->movementSpeed = 2.5f;
    this->size = 7.5f;
    this->destroyOnImpact = true;
}

void Bullet::init_hitbox()
{
    this->hitbox.setPosition(0.f, 360.f);
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

const float Bullet::getX() const
{
    return this->hitbox.getPosition().x;
} 

const float Bullet::getY() const
{
    return this->hitbox.getPosition().y;
}

const float Bullet::getSize() const
{
    return this->size;
}

const float Bullet::getSpeed() const
{
    return this->movementSpeed;
}

// Public Methods
void Bullet::move(const float dirX, const float dirY)
{
    this->hitbox.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}


void Bullet::update()
{

}

void Bullet::render(RenderTarget& target)
{
    target.draw(this->hitbox);
}
