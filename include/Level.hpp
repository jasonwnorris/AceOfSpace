// Level.hpp

#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

// STL Includes
#include <fstream>
#include <string>
// AOS Includes
#include "Vector2f.hpp"
#include "Asteroid.hpp"
#include "StraightShooter.hpp"
#include "TargetShooter.hpp"
#include "Kamikaze.hpp"
#include "Boss.hpp"

struct LevelObject
{
  std::string type;
  float positionX;
  float time;
};

class Level
{
  public:
    Level();

    static Level LevelOne;

    std::vector<LevelObject> LevelObjects;

    void BuildLevel();
    void AddObject(const std::string& type, float positionX, float spawnTime);
    void SpawnObject(LevelObject object);
    void Reset();

    void Update(float deltaTime);

    float timeElapsed;
    int objectIndex;
};

#endif
