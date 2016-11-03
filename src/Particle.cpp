// Particle.cpp

// AOS Includes
#include "Particle.hpp"

Particle::Particle(const std::string& keyname) : Object(keyname)
{
  m_LifeInterval = m_Sprite->m_Texture->m_FrameCount * m_Sprite->m_Texture->m_FrameInterval;
}

void Particle::Update(float deltaTime)
{
  m_LifeInterval -= deltaTime;

  if (m_LifeInterval < 0.0f)
  {
    Remove();
  }

  Object::Update(deltaTime);
}
