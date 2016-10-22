// Powerup.cpp //
#include "Powerup.h"

#include "Projectile.h"

Powerup::Powerup(string keyname) : Item(keyname)
{
	type = keyname;
}

void Powerup::InflictBonus(GameObject* object)
{
	if(type == "ItemHealth")
		object->health = Minimum(object->health + 50, PlayerHealth);
	else if(type == "ItemSpeed")
		object->speed += 25.0f;
	else if(type == "ItemBullets")
		object->weaponType = WEAPON_BULLET;
	else if(type == "ItemMissiles")
		object->weaponType = WEAPON_MISSILE;
	else if(type == "ItemFireball")
		object->weaponType = WEAPON_FIREBALL;
	else if(type == "ItemPlasma")
		object->weaponType = WEAPON_PLASMA;
}
