// Fireball.hpp

#ifndef __FIREBALL_HPP__
#define __FIREBALL_HPP__

// AOS Includes
#include "Projectile.hpp"

class Fireball : public Projectile
{
  public:
    Fireball(const std::string& p_Keyname);

    void Update(float p_DeltaTime);

  private:
    float m_LifeTimeRemaining;
};

#endif
