#include "BulletPattern.h"

//Private Methods
void BulletPattern::init_attributes()
{
    this->maxBullets = 25;
    this->bulletFireDelay = 0;
}

// Constructors / Destructors
BulletPattern::BulletPattern()
{
    this->init_attributes();
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
        bullet->set_fire_time(bullet->get_fire_time() + (this->bulletFireDelay*(this->pattern.size())));  //Add a delay proportional to the position of the bullet in the queue
        this->pattern.push_back(bullet);
    } else { 
        std::cout << "Max bullets for pattern reached." << std::endl;
    }
}

void BulletPattern::delete_bullet(int position)
{
    //Memory management
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

Bullet* BulletPattern::peek()
{
    return this->pattern.front();
}
