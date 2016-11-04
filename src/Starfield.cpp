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
  if (m_LastSpawn > c_StarfieldSpawnTime)
  {
    for (int i = 0; i < 3; ++i)
    {
      std::stringstream ss;
      ss << "Star" << (i + 1);

      Star* star = new Star(ss.str());
      star->SetPosition(Vector2f(static_cast<float>(rand() % c_ScreenWidth), -star->GetSprite()->GetOrigin().Y));
      star->SetSpeed(100.0f + i * 35.0f);
    }

    m_LastSpawn = 0.0f;
  }
}
