// Particle.cpp

// AOS Includes
#include "Particle.hpp"

Particle::Particle(const std::string& p_Keyname) : Object(p_Keyname)
{
  m_LifeInterval = m_Sprite->m_Texture->m_FrameCount * m_Sprite->m_Texture->m_FrameInterval;
}

void Particle::Update(float p_DeltaTime)
{
  m_LifeInterval -= p_DeltaTime;

  if (m_LifeInterval < 0.0f)
  {
    Remove();
  }

  Object::Update(p_DeltaTime);
}
