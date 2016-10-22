// Bullet.cpp //
#include "Bullet.hpp"

Bullet::Bullet(string keyname) : Projectile(keyname)
{
  speed = BulletSpeed;
  health = BulletHealth;
}
