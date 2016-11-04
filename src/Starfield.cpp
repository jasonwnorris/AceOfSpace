// Starfield.cpp

// STL Includes
#include <sstream>
// AOS Includes
#include "Starfield.hpp"

Starfield::Starfield()
{
  m_LastSpawn = 0.0f;
}

void Starfield::Update(float p_DeltaTime)
{
  m_LastSpawn += p_DeltaTime;
  if (m_LastSpawn > StarfieldSpawnTime)
  {
    for (int i = 0; i < 3; ++i)
    {
      std::stringstream ss;
      ss << "Star" << (i + 1);

      Star* star = new Star(ss.str());
      star->m_Position = Vector2f(static_cast<float>(rand() % ScreenWidth), -star->m_Sprite->m_Origin.Y);
      star->m_Speed = 100.0f + i * 35.0f;
    }

    m_LastSpawn = 0.0f;
  }
}
