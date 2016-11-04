// Projectile.hpp

#ifndef __PROJECTILE_HPP__
#define __PROJECTILE_HPP__

// AOS Includes
#include "GameObject.hpp"

class Projectile : public GameObject
{
  public:
    Projectile(const std::string& p_Keyname);

    void Collide(GameObject* p_GameObject);
};

#endif
