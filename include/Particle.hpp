// Particle.hpp

#ifndef __PARTICLE_HPP__
#define __PARTICLE_HPP__

// AOS Includes
#include "Object.hpp"

class Particle : public Object
{
  public:
    Particle(const std::string& p_Keyname);

    void Update(float p_DeltaTime);

  private:
    float m_LifeInterval;
};

#endif
