// Item.cpp

// AOS Includes
#include "Item.hpp"
#include "Player.hpp"

Item::Item(const std::string& keyname) : GameObject(keyname)
{
  direction = Vector2f::Down;
  speed = ItemSpeed;
  explosionKeyname = "Flash";
  CollisionList = &PlayerShip::PlayerShipList;
}

void Item::Collide(GameObject* object)
{
  InflictBonus(object);
  Explode();
  Remove();
}
