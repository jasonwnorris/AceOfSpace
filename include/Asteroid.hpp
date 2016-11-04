// Asteroid.hpp

#ifndef __ASTEROID_HPP__
#define __ASTEROID_HPP__

// AOS Includes
#include "Enemy.hpp"

class Asteroid : public Enemy
{
  public:
    Asteroid(const std::string& p_Keyname);

    void Explode();
};

#endif
