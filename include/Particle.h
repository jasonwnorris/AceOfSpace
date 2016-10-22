// Particle.h //
#ifndef PARTICLE_H
#define PARTICLE_H

#include "Object.h"

class Particle : public Object
{
  public:
    Particle(string keyname, Vector location);

    void Update(float deltaTime);

  private:
    float lifeInterval;
};

#endif
