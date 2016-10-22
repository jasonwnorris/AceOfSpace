// Kamikaze.h //
#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "Enemy.h"

class Kamikaze : public Enemy
{
	public:
		Kamikaze(string keyname);
		
		void Update(float deltaTime);
		
	private:
		float idleDelay;
		bool foundTarget;
};

#endif
