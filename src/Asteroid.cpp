// Asteroid.cpp

// AOS Includes
#include "Asteroid.hpp"

Asteroid::Asteroid(const std::string& p_Keyname) : Enemy(p_Keyname)
{
  m_PointValue = c_AsteroidPointValue;
  m_Health = c_AsteroidHealth;
  m_Speed = c_AsteroidSpeed;
}

void Asteroid::Explode()
{
  /*
  TO-DO: spawn rand() AsteroidSmall
  ** not enough time **
  */

  Enemy::Explode();
}
