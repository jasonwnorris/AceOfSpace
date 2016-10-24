// Asteroid.hpp

#ifndef __ASTEROID_HPP__
#define __ASTEROID_HPP__

#include "Enemy.hpp"

class Asteroid : public Enemy
{
  public:
    Asteroid(string keyname);

    void Explode();
};

#endif
