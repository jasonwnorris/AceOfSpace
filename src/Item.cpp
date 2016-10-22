// Item.cpp //
#include "Item.h"

#include "Player.h"

Item::Item(string keyname) : GameObject(keyname)
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
