// GameObject.cpp //
#include "GameObject.h"

#include "Particle.h"

GameObject::GameObject(string keyname) : Object(keyname)
{
  health = 0;
  flickerInterval = 0.0f;
  CollisionList = new vector<GameObject*>;
}

GameObject::~GameObject()
{
  delete CollisionList;
}

// check objects against those in its collision list
void GameObject::Update(float deltaTime)
{
    for(vector<GameObject*>::iterator Iter = CollisionList->begin(); Iter != CollisionList->end(); ++Iter)
        if(CheckCollision(this, (*Iter)))
            Collide((*Iter));

  if(flickerInterval > 0)
      flickerInterval -= deltaTime;
  else
      sprite->SetTextureIndex(0);
      
  Object::Update(deltaTime);

  RemoveOffScreen();
}

void GameObject::TakeDamage(int amount)
{
  if(health > 0)
  {
    health -= amount;

    if(health <= 0)
    {
      Explode();
        Remove();
    }
    else
    {
      sprite->SetTextureIndex(1);
      flickerInterval = DamageEffectTime;
    }
  }
}

// spawn a particle object when something dies
void GameObject::Explode()
{
  if(explosionKeyname != "")
      Particle* explosion = new Particle(explosionKeyname, position);
}

// check if the object bounds are intersecting with the viewable screen
void GameObject::RemoveOffScreen()
{
  SDL_Rect bounds = {0, 0, ScreenWidth, ScreenHeight};
  SDL_Rect intersect = Intersection(GetBounds(), bounds);

  if(intersect.w == 0 && intersect.h == 0)
      Remove();
}

// grabs a random object from a vector
GameObject* GameObject::PickRandomObject(vector<GameObject*>* PickList)
{
  int listSize = PickList->size();
  if(listSize > 0)
      return (*PickList)[rand() % listSize];
  else
      return NULL;
}
