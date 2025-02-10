#include "BulletPattern.h"

//Private Methods
void BulletPattern::init_attributes()
{
    this->maxBullets = 25;
}

// Constructors / Destructors
BulletPattern::BulletPattern()
{

}

BulletPattern::~BulletPattern()
{

}

//Accessors

const std::vector<Bullet*> BulletPattern::get_pattern() const
{
    return this->pattern;
}

//Methods
void BulletPattern::add_bullet(Bullet* bullet)
{
    this->pattern.push_back(bullet);
}

void BulletPattern::delete_bullet(int position)
{
    delete this->pattern.at(position);
    this->pattern.erase(this->pattern.begin() + position);
}
