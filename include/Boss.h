// Boss.h //
#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include "Miniboss.h"

class BossEnemy : public Enemy
{
	public:
		BossEnemy(string keyname);
		
		void Update(float deltaTime);
		void UpdateChildren();
		
		void RemoveOffScreen();
		void Remove();
		
	private:
		void FireBullet();

		Miniboss* leftHand;
		Miniboss* rightHand;

		float childrenAngle;
		float fireAngle;
		float lastFired;
};

class Boss
{
	public:
		Boss();
		
		static Boss FinalBoss;
		
		static void RemoveBoss();
		static void SpawnBoss();
		static void DestroyBoss();
		
		BossEnemy* boss;
		bool spawned;
		bool killed;
};

#endif
