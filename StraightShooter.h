// StraightShooter.h //
#ifndef STRAIGHT_SHOOTER_H
#define STRAIGHT_SHOOTER_H

#include "Enemy.h"

class StraightShooter : public Enemy
{
	public:
		StraightShooter(string keyname);

		virtual void Update(float deltaTime);

    private:
		void FireBullet();
		
		float lastFired;
};

#endif
