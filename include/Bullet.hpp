// Bullet.hpp

#ifndef __BULLET_HPP__
#define __BULLET_HPP__

// AOS Includes
#include "Projectile.hpp"

class Bullet : public Projectile
{
  public:
    Bullet(const std::string& p_Keyname);
};

#endif
