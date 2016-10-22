// Enemy.h //
#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject
{
	public:
		Enemy(string keyname);
		
		static vector<GameObject*> EnemyList;
		
		static void RemoveKilled();
		static void RemoveAll();
		
		void Explode();
		
	protected:
		int pointValue;
		
	private:
		void DropItem();
};

#endif
