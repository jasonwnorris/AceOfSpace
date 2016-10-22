// Bullet.cpp //
#include "Bullet.h"

Bullet::Bullet(string keyname) : Projectile(keyname)
{
	speed = BulletSpeed;
	health = BulletHealth;
}
