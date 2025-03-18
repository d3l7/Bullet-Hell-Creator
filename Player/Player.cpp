#include "Player.h"

using namespace sf;

// Private Methods
void Player::init_attributes()
{
    this->health = 5;
    this->movementSpeed = 3.f;
    this->size = 25.f;
}

void Player::init_hitbox()
{
    this->hitbox.setPosition(640.f, 360.f);  //Testing bullet interaction
    this->hitbox.setSize(Vector2f(this->size, this->size));
    this->hitbox.setFillColor(Color::Blue);
}

// Constructors / Destructors
Player::Player()
{
    this->init_attributes();
    this->init_hitbox();
}

Player::~Player()
{

}

//Accessors

//Getters
const int Player::get_health() const
{
    return this->health;
}

const float Player::get_size() const
{
    return this->size;
}

const Vector2f &Player::get_pos() const
{
    return this->hitbox.getPosition();
}

const FloatRect Player::get_bounds() const
{
    return this->hitbox.getGlobalBounds();
}

//Setters
void Player::set_health(const int health_change)
{
    this->health = this->health + health_change;
}

void Player::set_size(const float new_size)
{
    this->hitbox.setSize(Vector2f(new_size, new_size));
}

void Player::set_speed(const float new_speed)
{
    this->movementSpeed = new_speed;
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
