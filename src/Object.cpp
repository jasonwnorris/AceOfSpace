// Object.cpp

// AOS Includes
#include "Object.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

std::vector<Object*> Object::ObjectList;
std::vector<Object*> Object::ObjectAddList;

Object::Object(const std::string& keyname)
{
  m_Sprite = new Sprite(keyname);
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

void Object::UpdateObjects(float deltaTime)
{
  for (std::vector<Object*>::iterator Iter = ObjectList.begin(); Iter != ObjectList.end(); ++Iter)
  {
    (*Iter)->Update(deltaTime);
  }

  AddNew();
  RemoveDead();
}

void Object::Update(float deltaTime)
{
  m_Sprite->Update(deltaTime);
  m_Direction.Normalize();
  Move(m_Direction * m_Speed * deltaTime);
}

void Object::RenderObjects(SDL_Renderer* renderer)
{
  for (std::vector<Object*>::iterator Iter = ObjectList.begin(); Iter != ObjectList.end(); ++Iter)
  {
    (*Iter)->Render(renderer);
  }
}

void Object::Render(SDL_Renderer* renderer)
{
  m_Sprite->Render(renderer, m_Position);
}

void Object::AddNew()
{
  for (std::vector<Object*>::iterator Iter = ObjectAddList.begin(); Iter != ObjectAddList.end(); ++Iter)
  {
    ObjectList.push_back((*Iter));
  }

  ObjectAddList.clear();
}

void Object::RemoveDead()
{
  PlayerShip::RemoveKilled();
  Enemy::RemoveKilled();

  for (std::vector<Object*>::iterator Iter = ObjectList.begin(); Iter != ObjectList.end(); Iter += 0)
  {
    if ((*Iter)->m_IsDead)
    {
      Object* temp = (*Iter);
      Iter = ObjectList.erase(Iter);
      delete temp;
    }
    else
    {
      ++Iter;
    }
  }
}

void Object::RemoveAll()
{
  PlayerShip::RemoveAll();
  Enemy::RemoveAll();

  for (std::vector<Object*>::iterator Iter = ObjectList.begin(); Iter != ObjectList.end(); Iter += 0)
  {
    Object* temp = (*Iter);
    Iter = ObjectList.erase(Iter);
    delete temp;
  }

  ObjectList.clear();
}

void Object::Remove()
{
  m_IsDead = true;
}

void Object::Move(Vector2f amount)
{
  m_Position += amount;
}

SDL_Rect Object::GetBounds()
{
  SDL_Rect bounds;
  bounds.x = (Sint16)(m_Position.X - m_Sprite->m_Origin.X);
  bounds.y = (Sint16)(m_Position.Y - m_Sprite->m_Origin.Y);
  bounds.w = (Sint16)(m_Sprite->m_Texture->m_TileWidth);
  bounds.h = (Sint16)(m_Sprite->m_Texture->m_TileWidth);

  return bounds;
}

SDL_Rect Object::NormalizeBounds(const SDL_Rect& rect)
{
  SDL_Rect normalizeRect;
  normalizeRect.x = (Sint16)(rect.x + m_Sprite->GetFrameBounds().x + m_Sprite->m_Origin.X - m_Position.X);
  normalizeRect.y = (Sint16)(rect.y + m_Sprite->GetFrameBounds().y + m_Sprite->m_Origin.Y - m_Position.Y);
  normalizeRect.w = rect.w;
  normalizeRect.h = rect.h;

  return normalizeRect;
}

bool Object::CheckCollision(Object* objectA, Object* objectB)
{
  SDL_Rect boundsA = objectA->GetBounds();
  SDL_Rect boundsB = objectB->GetBounds();

  SDL_Rect collisionRect;
  if (SDL_IntersectRect(&boundsA, &boundsB, &collisionRect) == SDL_FALSE)
  {
    return false;
  }

  SDL_Rect normalA = objectA->NormalizeBounds(collisionRect);
  SDL_Rect normalB = objectB->NormalizeBounds(collisionRect);

  Texture* textureA = objectA->m_Sprite->m_Texture;
  Texture* textureB = objectB->m_Sprite->m_Texture;

  for (int y = 0; y <= collisionRect.h; ++y)
  {
    for (int x = 0; x <= collisionRect.w; ++x)
    {
      if (GetAlphaXY(textureA, normalA.x + x, normalA.y + y) && GetAlphaXY(textureB, normalB.x + x, normalB.y + y))
      {
        return true;
      }
    }
  }

  return false;
}

bool Object::GetAlphaXY(Texture* texture, int x, int y)
{
  return texture->m_IsPixelSolid[x + y * texture->m_Width];
}
