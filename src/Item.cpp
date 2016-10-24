// Item.cpp //
#include "Item.hpp"

#include "Player.hpp"

Item::Item(std::string keyname) : GameObject(keyname)
{
  direction = Vector(0, 1);
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
