// Level.h //
#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <string>
using namespace std;

#include "Vector.h"
#include "Asteroid.h"
#include "StraightShooter.h"
#include "TargetShooter.h"
#include "Kamikaze.h"
#include "Boss.h"

struct LevelObject
{
	string type;
	float positionX;
	float time;
};

class Level
{
	public:
		Level();
		
		static Level LevelOne;

		vector<LevelObject> LevelObjects;
		
		void BuildLevel();
		void AddObject(string type, float positionX, float spawnTime);
		void SpawnObject(LevelObject object);
		void Reset();

		void Update(float deltaTime);
		
		float timeElapsed;
		int objectIndex;
};

#endif
