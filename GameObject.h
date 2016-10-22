// GameObject.h //
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Object.h"

class GameObject : public Object
{
	public:
		GameObject(string keyname);
		~GameObject();
		
		virtual void Update(float deltaTime);

		virtual void Collide(GameObject* object) { }
		virtual void TakeDamage(int amount);
		virtual void Explode();

		virtual void RemoveOffScreen();
		
		GameObject* PickRandomObject(vector<GameObject*>* PickList);
		
		int health;
		float flickerInterval;
		string explosionKeyname;
		int weaponType;

		vector<GameObject*>* CollisionList;
};

#endif
