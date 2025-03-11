#pragma once

#include "../Bullet/Bullet.h"
#include <vector>

/*
    Class to act as a custom data structure to hold bullets
    - Implements the data structure to hold bullets
    - Sorts out order in which bullets should fire in
    - Adding queue like implementation in order to make a bullet pattern function properly
*/

class BulletPattern
{

private:
    //Data structures
    std::vector<Bullet*> pattern;

    //Attributes
    int maxBullets;
    int bulletFireDelay; 

    int patternSpawnTime;

    //Private Methods
    void init_attributes();

public:
    //Constructors / Destructors
    BulletPattern();
    ~BulletPattern();

    //Accessors
    const std::vector<Bullet*> get_pattern() const;

    //Methods
    void add_bullet(Bullet* bullet);
    void delete_bullet(int position);

    void load_pattern();

    bool is_full();
    bool is_empty();

    Bullet* peek();
};
