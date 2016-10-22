// Item.h //
#ifndef ITEM_H
#define ITEM_H

#include "GameObject.h"

class Item : public GameObject
{
	public:
		Item(string keyname);
		
		void Collide(GameObject* object);
		
		virtual void InflictBonus(GameObject* object) { }
};

#endif
