// Object.cpp

// STL Includes
#include <algorithm>
// AOS Includes
#include "Object.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

std::vector<Object*> Object::ObjectList;
std::vector<Object*> Object::ObjectAddList;

Object::Object(const std::string& p_Keyname)
{
  m_Sprite = new Sprite(p_Keyname);
  m_Position = Vector2f::Zero;
  m_Direction = Vector2f::Zero;
  m_Speed = 0.0f;
  m_IsDead = false;

  ObjectAddList.push_back(this);
}

Object::~Object()
{
  delete m_Sprite;
}

Sprite* Object::GetSprite() const
{
  return m_Sprite;
}

const Vector2f& Object::GetPosition() const
{
  return m_Position;
}

const Vector2f& Object::GetDirection() const
{
  return m_Direction;
}

float Object::GetSpeed() const
{
  return m_Speed;
}

bool Object::IsDead() const
{
  return m_IsDead;
}

void Object::SetPosition(const Vector2f& p_Position)
{
  m_Position = p_Position;
}

void Object::SetDirection(const Vector2f& p_Direction)
{
  m_Direction = p_Direction;
}

void Object::SetSpeed(float p_Speed)
{
  m_Speed = p_Speed;
}

void Object::UpdateObjects(float p_DeltaTime)
{
  for (Object* object : ObjectList)
  {
    object->Update(p_DeltaTime);
  }

  AddNew();
  RemoveDead();
}

void Object::Update(float p_DeltaTime)
{
  m_Sprite->Update(p_DeltaTime);

  m_Direction.Normalize();
  m_Position += m_Direction * m_Speed * p_DeltaTime;
}

void Object::RenderObjects(SDL_Renderer* p_Renderer)
{
  for (Object* object : ObjectList)
  {
    object->Render(p_Renderer);
  }
}

void Object::Render(SDL_Renderer* p_Renderer)
{
  m_Sprite->Render(p_Renderer, m_Position);
}

void Object::AddNew()
{
  ObjectList.insert(ObjectList.end(), ObjectAddList.begin(), ObjectAddList.end());
  ObjectAddList.clear();
}

void Object::RemoveDead()
{
  PlayerShip::RemoveKilled();
  Enemy::RemoveKilled();

  ObjectList.erase(std::remove_if(ObjectList.begin(), ObjectList.end(), [](Object* p_Object) {
    if (p_Object->IsDead())
    {
      delete p_Object;
    }
    return p_Object->IsDead();
  }), ObjectList.end());
}

void Object::RemoveAll()
{
  PlayerShip::RemoveAll();
  Enemy::RemoveAll();

  std::for_each(ObjectList.begin(), ObjectList.end(), [](Object* p_Object) { delete p_Object; });
  ObjectList.clear();
}

void Object::Remove()
{
  m_IsDead = true;
}

SDL_Rect Object::GetBounds()
{
  Texture* texture = m_Sprite->GetTexture();
  const Vector2f& origin = m_Sprite->GetOrigin();

  SDL_Rect bounds;
  bounds.x = static_cast<int>(m_Position.X - origin.X);
  bounds.y = static_cast<int>(m_Position.Y - origin.Y);
  bounds.w = texture->GetTileWidth();
  bounds.h = texture->GetTileHeight();

  return bounds;
}

SDL_Rect Object::NormalizeBounds(const SDL_Rect& p_Rectangle)
{
  const SDL_Rect bounds = m_Sprite->GetFrameBounds();
  const Vector2f& origin = m_Sprite->GetOrigin();

  SDL_Rect rectangle;
  rectangle.x = static_cast<int>(p_Rectangle.x + bounds.x + origin.X - m_Position.X);
  rectangle.y = static_cast<int>(p_Rectangle.y + bounds.y + origin.Y - m_Position.Y);
  rectangle.w = p_Rectangle.w;
  rectangle.h = p_Rectangle.h;

  return rectangle;
}

bool Object::CheckCollision(Object* p_ObjectA, Object* p_ObjectB)
{
  SDL_Rect boundsA = p_ObjectA->GetBounds();
  SDL_Rect boundsB = p_ObjectB->GetBounds();

  SDL_Rect collisionRect;
  if (SDL_IntersectRect(&boundsA, &boundsB, &collisionRect) == SDL_FALSE)
  {
    return false;
  }

  SDL_Rect normalA = p_ObjectB->NormalizeBounds(collisionRect);
  SDL_Rect normalB = p_ObjectB->NormalizeBounds(collisionRect);

  Texture* textureA = p_ObjectB->m_Sprite->GetTexture();
  Texture* textureB = p_ObjectB->m_Sprite->GetTexture();

  for (int y = 0; y <= collisionRect.h; ++y)
  {
    for (int x = 0; x <= collisionRect.w; ++x)
    {
      if (textureA->IsPixelSolid(normalA.x + x, normalA.y + y) && textureB->IsPixelSolid(normalB.x + x, normalB.y + y))
      {
        return true;
      }
    }
  }

  return false;
}
