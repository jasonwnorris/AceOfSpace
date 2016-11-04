// Projectile.hpp

#ifndef __PROJECTILE_HPP__
#define __PROJECTILE_HPP__

// AOS Includes
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
    Projectile(const std::string& p_Keyname);

    void Collide(GameObject* p_GameObject);
};

#endif
