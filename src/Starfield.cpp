// Starfield.cpp

// AOS Includes
#include "Starfield.hpp"

Starfield::Starfield()
{
  m_LastSpawn = 0.0f;
}

void Starfield::Update(float deltaTime)
{
  m_LastSpawn += deltaTime;

  if (m_LastSpawn > StarfieldSpawnTime)
  {
    for (int i = 0; i < 3; ++i)
    {
      char starkey[6];
      snprintf(starkey, 6, "Star%d", i + 1);

      Star* star = new Star(starkey);
      star->m_Position = Vector2f(static_cast<float>(rand() % ScreenWidth), -star->m_Sprite->m_Origin.Y);
      star->m_Speed = 100.0f + i * 35.0f;
    }

    m_LastSpawn = 0.0f;
  }
}
