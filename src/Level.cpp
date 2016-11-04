// Level.cpp

// STL Includes
#include <fstream>
// AOS Includes
#include "Asteroid.hpp"
#include "Boss.hpp"
#include "Kamikaze.hpp"
#include "Level.hpp"
#include "StraightShooter.hpp"
#include "TargetShooter.hpp"

Level::Level()
{
  m_TimeElapsed = 0.0f;
  m_ObjectIndex = 0;
}

bool Level::BuildLevel()
{
  Reset();

  std::ifstream file(c_LevelFilename, std::ios_base::in);
  if (!file.is_open())
  {
    SDL_Log("Failed to open file: %s", c_LevelFilename.c_str());
    return false;
  }

  std::string dummy;
  getline(file, dummy);

  float finalTime = 0.0f;
  while (!file.eof())
  {
    LevelObject object;
    file >> object.Type >> object.PositionX >> object.Time;
    m_LevelObjects.push_back(object);

    finalTime = object.Time;
  }

  file.close();

  LevelObject boss;
  boss.Type = "Boss";
  boss.PositionX = c_HalfScreenWidth;
  boss.Time = finalTime + 5.0f;
  m_LevelObjects.push_back(boss);

  return true;
}

void Level::SpawnObject(LevelObject p_LevelObject)
{
  if (p_LevelObject.Type == "Boss")
  {
    Boss::SpawnBoss();
  }
  else
  {
    Enemy* enemy = nullptr;

    if (p_LevelObject.Type == "Asteroid")
    {
      enemy = new Asteroid("Asteroid");
    }
    else if (p_LevelObject.Type == "StraightShooter")
    {
      enemy = new StraightShooter("StraightShooter");
    }
    else if (p_LevelObject.Type == "TargetShooter")
    {
      enemy = new TargetShooter("TargetShooter");
    }
    else if (p_LevelObject.Type == "Kamikaze")
    {
      enemy = new Kamikaze("Kamikaze");
    }

    enemy->SetPosition(Vector2f(p_LevelObject.PositionX, -enemy->GetSprite()->GetOrigin().Y));
  }
}

void Level::Reset()
{
  m_TimeElapsed = 0.0f;
  m_ObjectIndex = 0;

  m_LevelObjects.clear();
}

void Level::Update(float p_DeltaTime)
{
  m_TimeElapsed += p_DeltaTime;

  for (int i = m_ObjectIndex; i < m_LevelObjects.size(); ++i)
  {
    if (m_LevelObjects[i].Time > m_TimeElapsed)
    {
      break;
    }

    SpawnObject(m_LevelObjects[i]);
    ++m_ObjectIndex;
  }
}
