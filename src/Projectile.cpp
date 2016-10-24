// Projectile.cpp //
#include "Projectile.hpp"

Projectile::Projectile(std::string keyname) : GameObject(keyname)
{
  explosionKeyname = "Flash";
}

void Projectile::Collide(GameObject* object)
{
  int objectHealth = object->health;
  object->TakeDamage(this->health);
  this->TakeDamage(objectHealth);
}
