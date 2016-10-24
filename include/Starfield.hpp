// Starfield.hpp

#ifndef __STARFIELD_HPP__
#define __STARFIELD_HPP__

#include "Star.hpp"

class Starfield
{
  public:
    Starfield();

    void Update(float deltaTime);

  private:
    float lastSpawn;
};

#endif
