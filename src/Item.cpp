// Item.cpp

// AOS Includes
#include "Item.hpp"
#include "Player.hpp"

Item::Item(const std::string& p_Keyname) : GameObject(p_Keyname)
{
  m_Direction = Vector2f::Down;
  m_Speed = c_ItemSpeed;
  m_ExplosionKeyname = "Flash";
  CollisionList = &PlayerShip::PlayerShipList;
}

void Item::Collide(GameObject* p_GameObject)
{
  InflictBonus(p_GameObject);
  Explode();
  Remove();
}
