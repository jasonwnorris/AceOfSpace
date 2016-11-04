// Projectile.cpp

// AOS Includes
#include "Projectile.hpp"

Projectile::Projectile(const std::string& p_Keyname) : GameObject(p_Keyname)
{
  m_ExplosionKeyname = "Flash";
}

void Projectile::Collide(GameObject* p_GameObject)
{
  int objectHealth = p_GameObject->GetHealth();
  p_GameObject->TakeDamage(m_Health);
  TakeDamage(objectHealth);
}
