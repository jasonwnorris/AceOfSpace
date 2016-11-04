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
  std::string Type;
  float PositionX;
  float Time;
};

class Level
{
  public:
    Level();

    static Level LevelOne;

    std::vector<LevelObject> LevelObjects;

    void BuildLevel();
    void SpawnObject(LevelObject p_Object);
    void Reset();

    void Update(float p_DeltaTime);

    float m_TimeElapsed;
    int m_ObjectIndex;
};

#endif
