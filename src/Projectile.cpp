// Projectile.cpp

// AOS Includes
#include "Projectile.hpp"

Projectile::Projectile(const std::string& keyname) : GameObject(keyname)
{
  m_ExplosionKeyname = "Flash";
}

void Projectile::Collide(GameObject* object)
{
  int objectHealth = object->m_Health;
  object->TakeDamage(this->m_Health);
  this->TakeDamage(objectHealth);
}
