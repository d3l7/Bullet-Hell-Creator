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
    if (not this->is_full())
    {
    this->pattern.push_back(bullet);
    } else { 
        std::cout << "Max bullets for pattern reached." << std::endl;
    }
}

void BulletPattern::delete_bullet(int position)
{
    if (not this->is_empty())
    {
        delete this->pattern.at(position);
        this->pattern.erase(this->pattern.begin() + position);
    }
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

Bullet* BulletPattern::peek_bullet()
{
    return this->pattern.front();
}
