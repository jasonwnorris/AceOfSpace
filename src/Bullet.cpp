// Bullet.cpp

// AOS Includes
#include "Bullet.hpp"

Bullet::Bullet(const std::string& keyname) : Projectile(keyname)
{
  speed = BulletSpeed;
  health = BulletHealth;
}
