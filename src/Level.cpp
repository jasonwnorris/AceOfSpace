// Level.cpp

// AOS Includes
#include "Level.hpp"

Level Level::LevelOne;

Level::Level()
{
  timeElapsed = 0.0f;
  objectIndex = 0;
}

// open the text file and read in monster spawn information
void Level::BuildLevel()
{
  Reset();

  std::ifstream file;

  file.open("resources/level.txt");

  std::string type = "";
  int positionX = 0;
  float time = 0.0f;

  float finalTime = 0.0f;

  getline(file, type);

  while (!file.eof())
  {
    file >> type;
    file >> positionX;
    file >> time;

    AddObject(type, static_cast<float>(positionX), time);

    finalTime = time;
  }

  file.close();

  finalTime += 5.0f;

  AddObject("Boss", ScreenWidth / 2, finalTime);
}

// push the information onto the list
void Level::AddObject(const std::string& type, float positionX, float spawnTime)
{
  LevelObject object;
  object.type = type;
  object.positionX = positionX;
  object.time = spawnTime;

  LevelObjects.push_back(object);
}

// create a new enemy object according to the information in
// each LevelObject object
void Level::SpawnObject(LevelObject object)
{
  if (object.type == "Boss")
  {
    Boss::SpawnBoss();
  }
  else
  {
    Enemy* enemy = nullptr;

    if (object.type == "Asteroid")
    {
      enemy = new Asteroid("Asteroid");
    }
    else if (object.type == "StraightShooter")
    {
      enemy = new StraightShooter("StraightShooter");
    }
    else if (object.type == "TargetShooter")
    {
      enemy = new TargetShooter("TargetShooter");
    }
    else if (object.type == "Kamikaze")
    {
      enemy = new Kamikaze("Kamikaze");
    }

    enemy->position = Vector(object.positionX, -enemy->sprite->origin.Y);
  }
}

void Level::Reset()
{
  timeElapsed = 0.0f;
  objectIndex = 0;

  LevelObjects.clear();
}

// scan through the LevelObjects to see if its spawn time has passed
// then spawn the object and increment the index so an item doesn't
// spawn again
void Level::Update(float deltaTime)
{
  timeElapsed += deltaTime;

  for (int i = objectIndex; i < LevelObjects.size(); ++i)
  {
    if (LevelObjects[i].time > timeElapsed)
    {
      break;
    }

    SpawnObject(LevelObjects[i]);
    objectIndex++;
  }
}
