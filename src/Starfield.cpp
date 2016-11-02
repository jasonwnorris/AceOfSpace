// Starfield.cpp

// AOS Includes
#include "Starfield.hpp"

Starfield::Starfield()
{
  lastSpawn = 0.0f;
}

void Starfield::Update(float deltaTime)
{
  lastSpawn += deltaTime;

  if (lastSpawn > StarfieldSpawnTime)
  {
    for (int i = 0; i < 3; ++i)
    {
      char starkey[6];
      snprintf(starkey, 6, "Star%d", i + 1);

      Star* star = new Star(starkey);
      star->position = Vector(static_cast<float>(rand() % ScreenWidth), -star->sprite->origin.Y);
      star->speed = 100.0f + i * 35.0f;
    }

    lastSpawn = 0.0f;
  }
}
