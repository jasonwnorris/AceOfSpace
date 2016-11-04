// Projectile.cpp

// AOS Includes
#include "Projectile.hpp"

Projectile::Projectile(const std::string& p_Keyname) : GameObject(p_Keyname)
{
  m_ExplosionKeyname = "Flash";
}

void Projectile::Collide(GameObject* p_GameObject)
{
  int objectHealth = p_GameObject->m_Health;
  p_GameObject->TakeDamage(m_Health);
  this->TakeDamage(objectHealth);
}
