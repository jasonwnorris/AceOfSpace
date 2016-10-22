// Object.h //
#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
using namespace std;

#include "sprite.h"

class Object
{
	public:
		Object(string keyname);
		~Object();

		static vector<Object*> ObjectList;
		static vector<Object*> ObjectAddList;
		
		static void UpdateObjects(float deltaTime);
		virtual void Update(float deltaTime);
		
		static void RenderObjects(SDL_Surface* screen);
		virtual void Render(SDL_Surface* screen);

		static void AddNew();
		static void RemoveDead();
		static void RemoveAll();
		virtual void Remove();

		void Move(Vector amount);

		SDL_Rect GetBounds();
		SDL_Rect NormalizeBounds(const SDL_Rect& rect);
		static SDL_Rect Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB);
		static bool CheckCollision(Object* objectA, Object* objectB);
		static bool GetAlphaXY(Object* object, int x, int y);
		static bool GetAlphaXY(SDL_Surface* surface, int x, int y);

		Sprite* sprite;
		Vector position;
		Vector direction;
		float speed;
		bool dead;
};

#endif
