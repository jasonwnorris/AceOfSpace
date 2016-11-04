// Starfield.hpp

#ifndef __STARFIELD_HPP__
#define __STARFIELD_HPP__

// AOS Includes
#include "Star.hpp"

class Starfield
{
  public:
    Starfield();

    void Update(float p_DeltaTime);

  private:
    float m_LastSpawn;
};

#endif
