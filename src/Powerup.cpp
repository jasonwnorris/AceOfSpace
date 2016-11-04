// Powerup.cpp

// STL Includes
#include <algorithm>
// AOS Includes
#include "Powerup.hpp"
#include "Projectile.hpp"

Powerup::Powerup(const std::string& p_Keyname) : Item(p_Keyname)
{
  m_Type = p_Keyname;
}

void Powerup::InflictBonus(GameObject* p_Object)
{
  if (m_Type == "ItemHealth")
  {
    p_Object->m_Health = std::min(p_Object->m_Health + 50, PlayerHealth);
  }
  else if (m_Type == "ItemSpeed")
  {
    p_Object->m_Speed += 25.0f;
  }
  else if (m_Type == "ItemBullets")
  {
    p_Object->m_WeaponType = WEAPON_BULLET;
  }
  else if (m_Type == "ItemMissiles")
  {
    p_Object->m_WeaponType = WEAPON_MISSILE;
  }
  else if (m_Type == "ItemFireball")
  {
    p_Object->m_WeaponType = WEAPON_FIREBALL;
  }
  else if (m_Type == "ItemPlasma")
  {
    p_Object->m_WeaponType = WEAPON_PLASMA;
  }
}
