#include "Missile.h"

Missile::Missile(string keyname) : Projectile(keyname)
{
	speed = MissileSpeed;
	health = MissileHealth;
	target = NULL;
}

// point the missile at its target, but very slowly
void Missile::Update(float deltaTime)
{
	if(target == NULL || target->dead)
		target = PickRandomObject(CollisionList);
	    
	if(target != NULL)
	{
        Vector targetDirection = target->position - position;
        targetDirection.Normalize();
        direction += targetDirection * MissileHomingStrength;
	}
	
	Projectile::Update(deltaTime);
}

// give the missile some space to go offscreen and fly back on
void Missile::RemoveOffScreen()
{
	SDL_Rect bounds = {-ScreenWidth / 2, -ScreenHeight / 2, ScreenWidth * 2, ScreenHeight * 2};
	SDL_Rect intersect = Intersection(GetBounds(), bounds);

	if(intersect.w == 0 && intersect.h == 0)
	    Remove();
}
