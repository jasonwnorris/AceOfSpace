// Level.cpp

// AOS Includes
#include "Level.hpp"

Level Level::LevelOne;

Level::Level()
{
  m_TimeElapsed = 0.0f;
  m_ObjectIndex = 0;
}

void Level::BuildLevel()
{
  Reset();

  std::ifstream file;

  file.open("resources/level.txt");

  std::string type = "";
  float positionX = 0.0f;
  float time = 0.0f;

  float finalTime = 0.0f;

  getline(file, type);

  while (!file.eof())
  {
    file >> type;
    file >> positionX;
    file >> time;

    LevelObject object;
    object.Type = type;
    object.PositionX = positionX;
    object.Time = time;

    LevelObjects.push_back(object);

    finalTime = time;
  }

  file.close();

  LevelObject boss;
  boss.Type = "Boss";
  boss.PositionX = c_ScreenWidth / 2;
  boss.Time = finalTime + 5.0f;

  LevelObjects.push_back(boss);
}

void Level::SpawnObject(LevelObject p_Object)
{
  if (p_Object.Type == "Boss")
  {
    Boss::SpawnBoss();
  }
  else
  {
    Enemy* enemy = nullptr;

    if (p_Object.Type == "Asteroid")
    {
      enemy = new Asteroid("Asteroid");
    }
    else if (p_Object.Type == "StraightShooter")
    {
      enemy = new StraightShooter("StraightShooter");
    }
    else if (p_Object.Type == "TargetShooter")
    {
      enemy = new TargetShooter("TargetShooter");
    }
    else if (p_Object.Type == "Kamikaze")
    {
      enemy = new Kamikaze("Kamikaze");
    }

    enemy->m_Position = Vector2f(p_Object.PositionX, -enemy->m_Sprite->m_Origin.Y);
  }
}

void Level::Reset()
{
  m_TimeElapsed = 0.0f;
  m_ObjectIndex = 0;

  LevelObjects.clear();
}

void Level::Update(float p_DeltaTime)
{
  m_TimeElapsed += p_DeltaTime;

  for (int i = m_ObjectIndex; i < LevelObjects.size(); ++i)
  {
    if (LevelObjects[i].Time > m_TimeElapsed)
    {
      break;
    }

    SpawnObject(LevelObjects[i]);
    m_ObjectIndex++;
  }
}
