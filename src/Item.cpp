// Item.cpp

// AOS Includes
#include "Item.hpp"
#include "Player.hpp"

Item::Item(const std::string& p_Keyname) : GameObject(p_Keyname)
{
  m_Direction = Vector2f::Down;
  m_Speed = ItemSpeed;
  m_ExplosionKeyname = "Flash";
  CollisionList = &PlayerShip::PlayerShipList;
}

void Item::Collide(GameObject* p_Object)
{
  InflictBonus(p_Object);
  Explode();
  Remove();
}
