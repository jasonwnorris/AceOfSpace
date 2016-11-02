// Fireball.hpp

#ifndef __FIREBALL_HPP__
#define __FIREBALL_HPP__

// AOS Includes
#include "Projectile.hpp"

class Fireball : public Projectile
{
  public:
    Fireball(std::string keyname);

    void Update(float deltaTime);

  private:
    float lifeTimeRemaining;
};

#endif
