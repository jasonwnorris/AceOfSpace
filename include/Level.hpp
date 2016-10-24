// Level.hpp

#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include <fstream>
#include <string>
using namespace std;

#include "Vector.hpp"
#include "Asteroid.hpp"
#include "StraightShooter.hpp"
#include "TargetShooter.hpp"
#include "Kamikaze.hpp"
#include "Boss.hpp"

struct LevelObject
{
  string type;
  float positionX;
  float time;
};

class Level
{
  public:
    Level();

    static Level LevelOne;

    vector<LevelObject> LevelObjects;

    void BuildLevel();
    void AddObject(string type, float positionX, float spawnTime);
    void SpawnObject(LevelObject object);
    void Reset();

    void Update(float deltaTime);

    float timeElapsed;
    int objectIndex;
};

#endif
