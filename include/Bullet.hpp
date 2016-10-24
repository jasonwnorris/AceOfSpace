// Bullet.hpp

#ifndef __BULLET_HPP__
#define __BULLET_HPP__

#include "Projectile.hpp"

class Bullet : public Projectile
{
  public:
    Bullet(std::string keyname);
};

#endif
