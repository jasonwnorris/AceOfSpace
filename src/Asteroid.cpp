// Asteroid.cpp

// AOS Includes
#include "Asteroid.hpp"

Asteroid::Asteroid(std::string keyname) : Enemy(keyname)
{
  pointValue = AsteroidPointValue;
  health = AsteroidHealth;
  speed = AsteroidSpeed;
}

void Asteroid::Explode()
{
  /*
  TO-DO: spawn rand() AsteroidSmall
  ** not enough time **
  */

  Enemy::Explode();
}
