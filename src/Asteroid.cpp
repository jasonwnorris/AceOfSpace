// Asteroid.cpp

// AOS Includes
#include "Asteroid.hpp"

Asteroid::Asteroid(const std::string& keyname) : Enemy(keyname)
{
  m_PointValue = AsteroidPointValue;
  m_Health = AsteroidHealth;
  m_Speed = AsteroidSpeed;
}

void Asteroid::Explode()
{
  /*
  TO-DO: spawn rand() AsteroidSmall
  ** not enough time **
  */

  Enemy::Explode();
}
