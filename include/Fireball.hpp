// Fireball.hpp

#ifndef __FIREBALL_HPP__
#define __FIREBALL_HPP__

#include "Projectile.hpp"

class Fireball : public Projectile
{
  public:
    Fireball(string keyname);

    void Update(float deltaTime);

  private:
    float lifeTimeRemaining;
};

#endif
