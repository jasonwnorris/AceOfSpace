// Starfield.cpp //
#include "Starfield.h"

Starfield::Starfield()
{
	lastSpawn = 0.0f;
}

void Starfield::Update(float deltaTime)
{
	lastSpawn += deltaTime;
	
	if(lastSpawn > StarfieldSpawnTime)
	{
		for(int i = 0; i < 3; ++i)
		{
        	char starkey[5];
			sprintf(starkey, "Star%d", i + 1);
			
			Star* star = new Star(starkey);
			star->position = Vector(rand() % ScreenWidth, -star->sprite->origin.Y);
			star->speed = 100.0f + i * 35.0f;
		}
		
		lastSpawn = 0.0f;
	}
}
