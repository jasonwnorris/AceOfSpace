// Fireball.cpp

// AOS Includes
#include "Fireball.hpp"

Fireball::Fireball(const std::string& p_Keyname) : Projectile(p_Keyname)
{
  m_Speed = c_FireballSpeed;
  m_Health = c_FireballHealth;
  m_LifeTimeRemaining = c_FireballFadeoutTime;
}

void Fireball::Update(float p_DeltaTime)
{
  Projectile::Update(p_DeltaTime);

  m_LifeTimeRemaining -= p_DeltaTime;

  if (m_LifeTimeRemaining < 0)
  {
    Remove();
  }
}
