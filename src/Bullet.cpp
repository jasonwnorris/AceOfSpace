// Bullet.cpp

// AOS Includes
#include "Bullet.hpp"

Bullet::Bullet(const std::string& keyname) : Projectile(keyname)
{
  m_Speed = BulletSpeed;
  m_Health = BulletHealth;
}
