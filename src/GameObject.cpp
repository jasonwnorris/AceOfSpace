// GameObject.cpp

// AOS Includes
#include "GameObject.hpp"
#include "Particle.hpp"

GameObject::GameObject(const std::string& p_Keyname) : Object(p_Keyname)
{
  m_Health = 0;
  m_FlickerInterval = 0.0f;
  m_CollisionList = nullptr;
}

GameObject::~GameObject()
{
}

int GameObject::GetHealth() const
{
  return m_Health;
}

void GameObject::SetHealth(int p_Health)
{
  m_Health = p_Health;
}

void GameObject::SetWeaponType(int p_WeaponType)
{
  m_WeaponType = p_WeaponType;
}

void GameObject::SetCollisionList(std::vector<GameObject*>* p_CollisionList)
{
  m_CollisionList = p_CollisionList;
}

void GameObject::Update(float p_DeltaTime)
{
  if (m_CollisionList != nullptr)
  {
    for (std::vector<GameObject*>::iterator Iter = m_CollisionList->begin(); Iter != m_CollisionList->end(); ++Iter)
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

void GameObject::Collide(GameObject* p_GameObject)
{
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
      m_FlickerInterval = c_DamageEffectTime;
    }
  }
}

void GameObject::Explode()
{
  if (!m_ExplosionKeyname.empty())
  {
    Particle* explosion = new Particle(m_ExplosionKeyname);
    explosion->SetPosition(m_Position);
  }
}

void GameObject::RemoveOffScreen()
{
  SDL_Rect screenBounds = { 0, 0, c_ScreenWidth, c_ScreenHeight };
  SDL_Rect objectBounds = GetBounds();

  if (SDL_HasIntersection(&screenBounds, &objectBounds) == SDL_FALSE)
  {
    Remove();
  }
}

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
