// Projectile.hpp

#ifndef __PROJECTILE_HPP__
#define __PROJECTILE_HPP__

#include "GameObject.hpp"

enum WeaponType
{
  WEAPON_BULLET,
  WEAPON_MISSILE,
  WEAPON_FIREBALL,
  WEAPON_PLASMA
};

class Projectile : public GameObject
{
  public:
    Projectile(std::string keyname);

    void Collide(GameObject* object);
};

#endif
