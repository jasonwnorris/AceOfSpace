// Missile.hpp

#ifndef __MISSILE_HPP__
#define __MISSILE_HPP__

#include "Projectile.hpp"

class Missile : public Projectile
{
  public:
    Missile(std::string keyname);

    void Update(float deltaTime);

    void RemoveOffScreen();

  private:
    GameObject* target;
};

#endif
