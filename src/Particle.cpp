// Particle.cpp //
#include "Particle.hpp"

Particle::Particle(std::string keyname, Vector location) : Object(keyname)
{
  position = location;
  lifeInterval = sprite->texture->frameCount * sprite->texture->frameInterval;
}

void Particle::Update(float deltaTime)
{
  lifeInterval -= deltaTime;

  if (lifeInterval < 0)
  {
    Remove();
  }

  Object::Update(deltaTime);
}
