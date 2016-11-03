// Starfield.hpp

#ifndef __STARFIELD_HPP__
#define __STARFIELD_HPP__

// AOS Includes
#include "Star.hpp"

class Starfield
{
  public:
    Starfield();

    void Update(float deltaTime);

  private:
    float m_LastSpawn;
};

#endif
