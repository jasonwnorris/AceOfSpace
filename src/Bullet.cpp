// Bullet.cpp

// AOS Includes
#include "Bullet.hpp"

Bullet::Bullet(const std::string& p_Keyname) : Projectile(p_Keyname)
{
  m_Speed = BulletSpeed;
  m_Health = BulletHealth;
}
