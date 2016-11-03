// Fireball.cpp

// AOS Includes
#include "Fireball.hpp"

Fireball::Fireball(const std::string& keyname) : Projectile(keyname)
{
  m_Speed = FireballSpeed;
  m_Health = FireballHealth;
  m_LifeTimeRemaining = FireballFadeoutTime;
}

void Fireball::Update(float deltaTime)
{
  Projectile::Update(deltaTime);

  m_LifeTimeRemaining -= deltaTime;

  if (m_LifeTimeRemaining < 0)
  {
    Remove();
  }
}
