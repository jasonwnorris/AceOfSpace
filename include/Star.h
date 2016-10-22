// Star.h //
#ifndef STAR_H
#define STAR_H

#include "Object.h"

class Star : public Object
{
	public:
		Star(string keyname);
		
		void Update(float deltaTime);
};

#endif
