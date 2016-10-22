// Asteroid.h //
#ifndef ASTEROID_H
#define ASTEROID_H

#include "Enemy.hpp"

class Asteroid : public Enemy
{
  public:
    Asteroid(string keyname);

    void Explode();
};

#endif
