// Level.hpp

#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

// STL Includes
#include <vector>
// AOS Includes
#include "LevelObject.hpp"

class Level
{
  public:
    Level();

    bool BuildLevel();
    void SpawnObject(LevelObject p_LevelObject);
    void Reset();

    void Update(float p_DeltaTime);

    float m_TimeElapsed;
    int m_ObjectIndex;
    std::vector<LevelObject> m_LevelObjects;
};

#endif
