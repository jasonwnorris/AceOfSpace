// Particle.cpp

// AOS Includes
#include "Particle.hpp"

Particle::Particle(const std::string& keyname) : Object(keyname)
{
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
