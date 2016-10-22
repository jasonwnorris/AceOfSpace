// Powerup.h //
#ifndef POWERUP_H
#define POWERUP_H

#include "Item.h"

class Powerup : public Item
{
	public:
		Powerup(string keyname);
		
		void InflictBonus(GameObject* object);
		
	private:
		string type;
};

#endif
