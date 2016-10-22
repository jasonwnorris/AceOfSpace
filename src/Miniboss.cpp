// Miniboss.cpp //
#include "Miniboss.h"

#include "math.h"
#include "Bullet.h"
#include "Player.h"

Miniboss::Miniboss(string keyname) : Enemy(keyname)
{
	pointValue = MinibossPointValue;
	health = MinibossHealth;
	position = Vector(0, -ScreenHeight / 2);

	lastFired = 0.0f;
}

void Miniboss::Update(float deltaTime)
{
	Enemy::Update(deltaTime);
	
	lastFired += deltaTime;
	if(lastFired > MinibossFireDelay)
	    FireBullet();
}

void Miniboss::RemoveOffScreen()
{
	SDL_Rect bounds = {-ScreenWidth, -ScreenHeight, ScreenWidth * 3, ScreenHeight * 3};
	SDL_Rect intersect = Intersection(GetBounds(), bounds);

	if(intersect.w == 0 && intersect.h == 0)
	    Remove();
}

// fire bullets in an octagon shape pattern
void Miniboss::FireBullet()
{
	for(int i = 0; i < 8; i++)
	{
		Bullet* bullet = new Bullet("NeonCross");
	    bullet->position = position;
	    bullet->direction = Vector::CalculateDirection(i * (M_PI / 4) + (M_PI / 8));
	    bullet->speed = 150.0f;
	    bullet->CollisionList = &PlayerShip::PlayerShipList;
	}

    lastFired = 0.0f;
}
