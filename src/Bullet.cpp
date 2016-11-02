// Bullet.cpp

// AOS Includes
#include "Bullet.hpp"

Bullet::Bullet(std::string keyname) : Projectile(keyname)
{
  speed = BulletSpeed;
  health = BulletHealth;
}
