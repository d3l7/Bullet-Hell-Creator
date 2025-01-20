#include "Player.h"

using namespace sf;

//Private Methods
void Player::init_hitbox()
{
    this->hitbox.setSize(Vector2f(this->size, this->size));
    this->hitbox.setFillColor(Color::Blue);
}

// Constructors / Destructors
Player::Player()
{
    this->movementSpeed = 3.f;
    this->size = 25.f;

    this->init_hitbox();
}

Player::~Player()
{

}

//Accessors

const float Player::getX() const
{
    return this->hitbox.getPosition().x;
}

const float Player::getY() const
{
    return this->hitbox.getPosition().y;
}

const float Player::getSize() const
{
    return this->size;
}

//Methods

void Player::move(const float dirX, const float dirY)
{
    this->hitbox.move(this->movementSpeed * dirX, this->movementSpeed * dirY);  //Only need to then catch inputs of dirX and dirY to manipulate which way the ship goes, can also add multipliers and stuffs :D
}

void Player::update()
{

}

void Player::render(RenderTarget& target)
{
    target.draw(this->hitbox);
}
