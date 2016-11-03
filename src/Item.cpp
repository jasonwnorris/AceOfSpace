// Item.cpp

// AOS Includes
#include "Item.hpp"
#include "Player.hpp"

Item::Item(const std::string& keyname) : GameObject(keyname)
{
  m_Direction = Vector2f::Down;
  m_Speed = ItemSpeed;
  m_ExplosionKeyname = "Flash";
  CollisionList = &PlayerShip::PlayerShipList;
}

void Item::Collide(GameObject* object)
{
  InflictBonus(object);
  Explode();
  Remove();
}
