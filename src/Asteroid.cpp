// Asteroid.cpp

// AOS Includes
#include "Asteroid.hpp"

Asteroid::Asteroid(const std::string& p_Keyname) : Enemy(p_Keyname)
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
