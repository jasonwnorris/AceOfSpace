// Fireball.cpp //
#include "Fireball.hpp"

Fireball::Fireball(std::string keyname) : Projectile(keyname)
{
  speed = FireballSpeed;
  health = FireballHealth;
  lifeTimeRemaining = FireballFadeoutTime;
}

void Fireball::Update(float deltaTime)
{
  Projectile::Update(deltaTime);
  
  lifeTimeRemaining -= deltaTime;
  
  if (lifeTimeRemaining < 0)
    Remove();
}
