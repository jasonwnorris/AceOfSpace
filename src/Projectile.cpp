// Projectile.cpp

// AOS Includes
#include "Projectile.hpp"

Projectile::Projectile(const std::string& p_Keyname) : GameObject(p_Keyname)
{
  m_ExplosionKeyname = "Flash";
}

void Projectile::Collide(GameObject* p_Object)
{
  int objectHealth = p_Object->m_Health;
  p_Object->TakeDamage(m_Health);
  this->TakeDamage(objectHealth);
}
