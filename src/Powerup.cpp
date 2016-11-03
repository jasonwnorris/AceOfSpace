// Powerup.cpp

// STL Includes
#include <algorithm>
// AOS Includes
#include "Powerup.hpp"
#include "Projectile.hpp"

Powerup::Powerup(const std::string& keyname) : Item(keyname)
{
  m_Type = keyname;
}

void Powerup::InflictBonus(GameObject* object)
{
  if (m_Type == "ItemHealth")
  {
    object->m_Health = std::min(object->m_Health + 50, PlayerHealth);
  }
  else if (m_Type == "ItemSpeed")
  {
    object->m_Speed += 25.0f;
  }
  else if (m_Type == "ItemBullets")
  {
    object->m_WeaponType = WEAPON_BULLET;
  }
  else if (m_Type == "ItemMissiles")
  {
    object->m_WeaponType = WEAPON_MISSILE;
  }
  else if (m_Type == "ItemFireball")
  {
    object->m_WeaponType = WEAPON_FIREBALL;
  }
  else if (m_Type == "ItemPlasma")
  {
    object->m_WeaponType = WEAPON_PLASMA;
  }
}
