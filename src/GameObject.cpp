// GameObject.cpp //
#include "GameObject.hpp"

#include "Particle.hpp"

GameObject::GameObject(std::string keyname) : Object(keyname)
{
  health = 0;
  flickerInterval = 0.0f;
  CollisionList = nullptr;
}

GameObject::~GameObject()
{
}

// check objects against those in its collision list
void GameObject::Update(float deltaTime)
{
  if (CollisionList != nullptr)
  {
    for (std::vector<GameObject*>::iterator Iter = CollisionList->begin(); Iter != CollisionList->end(); ++Iter)
    {
      if (CheckCollision(this, (*Iter)))
      {
        Collide((*Iter));
      }
    }
  }

  if (flickerInterval > 0)
  {
    flickerInterval -= deltaTime;
  }
  else
  {
    sprite->SetTextureIndex(0);
  }

  Object::Update(deltaTime);

  RemoveOffScreen();
}

void GameObject::TakeDamage(int amount)
{
  if (health > 0)
  {
    health -= amount;

    if (health <= 0)
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
  if (explosionKeyname != "")
  {
    Particle* explosion = new Particle(explosionKeyname);
    explosion->position = position;
  }
}

// check if the object bounds are intersecting with the viewable screen
void GameObject::RemoveOffScreen()
{
  SDL_Rect screenBounds = {0, 0, ScreenWidth, ScreenHeight};
  SDL_Rect objectBounds = GetBounds();

  if (SDL_HasIntersection(&screenBounds, &objectBounds) == SDL_FALSE)
  {
    Remove();
  }
}

// grabs a random object from a std::vector
GameObject* GameObject::PickRandomObject(std::vector<GameObject*>* PickList)
{
  int listSize = PickList->size();
  if (listSize > 0)
  {
    return (*PickList)[rand() % listSize];
  }
  else
  {
    return nullptr;
  }
}
