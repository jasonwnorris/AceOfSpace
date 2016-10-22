// Projectile.h //
#ifndef PROJECTILE_H
#define PROJECTILE_H

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
    Projectile(string keyname);

    void Collide(GameObject* object);
};

#endif
