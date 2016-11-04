// GameObject.cpp

// AOS Includes
#include "GameObject.hpp"
#include "Particle.hpp"

GameObject::GameObject(const std::string& p_Keyname) : Object(p_Keyname)
{
  m_Health = 0;
  m_FlickerInterval = 0.0f;
  CollisionList = nullptr;
}

GameObject::~GameObject()
{
}

// check objects against those in its collision list
void GameObject::Update(float p_DeltaTime)
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

  if (m_FlickerInterval > 0)
  {
    m_FlickerInterval -= p_DeltaTime;
  }
  else
  {
    m_Sprite->SetTextureIndex(0);
  }

  Object::Update(p_DeltaTime);

  RemoveOffScreen();
}

void GameObject::TakeDamage(int p_Amount)
{
  if (m_Health > 0)
  {
    m_Health -= p_Amount;

    if (m_Health <= 0)
    {
      Explode();
      Remove();
    }
    else
    {
      m_Sprite->SetTextureIndex(1);
      m_FlickerInterval = DamageEffectTime;
    }
  }
}

// spawn a particle object when something dies
void GameObject::Explode()
{
  if (m_ExplosionKeyname != "")
  {
    Particle* explosion = new Particle(m_ExplosionKeyname);
    explosion->m_Position = m_Position;
  }
}

// check if the object bounds are intersecting with the viewable screen
void GameObject::RemoveOffScreen()
{
  SDL_Rect screenBounds = { 0, 0, ScreenWidth, ScreenHeight };
  SDL_Rect objectBounds = GetBounds();

  if (SDL_HasIntersection(&screenBounds, &objectBounds) == SDL_FALSE)
  {
    Remove();
  }
}

// grabs a random object from a std::vector
GameObject* GameObject::PickRandomObject(std::vector<GameObject*>* p_PickList)
{
  int listSize = static_cast<int>(p_PickList->size());
  if (listSize > 0)
  {
    return (*p_PickList)[rand() % listSize];
  }
  else
  {
    return nullptr;
  }
}
