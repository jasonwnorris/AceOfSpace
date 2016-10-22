// Asteroid.h //
#ifndef ASTEROID_H
#define ASTEROID_H

#include "Enemy.h"

class Asteroid : public Enemy
{
	public:
		Asteroid(string keyname);
		
		void Explode();
};

#endif
