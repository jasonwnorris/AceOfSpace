// Asteroid.cpp //
#include "Asteroid.hpp"

Asteroid::Asteroid(string keyname) : Enemy(keyname)
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
