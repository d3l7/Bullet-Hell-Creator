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

//Methods
void BulletPattern::add_bullet(Bullet* bullet)
{
    this->pattern.push_back(bullet);
}

void BulletPattern::delete_bullet(int position)
{

}

bool BulletPattern::is_full() 
{
    if (this->pattern.size() == maxBullets)
    {
        return true;
    } else {
        return false;
    }
}

bool BulletPattern::is_empty()
{
    if (this->pattern.size() < 0)
    {
        return true;
    } else {
        return false;
    }
}
