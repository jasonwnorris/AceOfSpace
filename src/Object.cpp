// Object.cpp

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

void Object::UpdateObjects(float p_DeltaTime)
{
  for (std::vector<Object*>::iterator Iter = ObjectList.begin(); Iter != ObjectList.end(); ++Iter)
  {
    (*Iter)->Update(p_DeltaTime);
  }

  AddNew();
  RemoveDead();
}

void Object::Update(float p_DeltaTime)
{
  m_Sprite->Update(p_DeltaTime);
  m_Direction.Normalize();
  Move(m_Direction * m_Speed * p_DeltaTime);
}

void Object::RenderObjects(SDL_Renderer* p_Renderer)
{
  for (std::vector<Object*>::iterator Iter = ObjectList.begin(); Iter != ObjectList.end(); ++Iter)
  {
    (*Iter)->Render(p_Renderer);
  }
}

void Object::Render(SDL_Renderer* p_Renderer)
{
  m_Sprite->Render(p_Renderer, m_Position);
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

void Object::Move(Vector2f p_Amount)
{
  m_Position += p_Amount;
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

SDL_Rect Object::NormalizeBounds(const SDL_Rect& p_Rect)
{
  SDL_Rect rect;
  rect.x = (Sint16)(p_Rect.x + m_Sprite->GetFrameBounds().x + m_Sprite->m_Origin.X - m_Position.X);
  rect.y = (Sint16)(p_Rect.y + m_Sprite->GetFrameBounds().y + m_Sprite->m_Origin.Y - m_Position.Y);
  rect.w = p_Rect.w;
  rect.h = p_Rect.h;

  return rect;
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

  Texture* textureA = p_ObjectB->m_Sprite->m_Texture;
  Texture* textureB = p_ObjectB->m_Sprite->m_Texture;

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

bool Object::GetAlphaXY(Texture* p_Texture, int p_X, int p_Y)
{
  return p_Texture->m_IsPixelSolid[p_X + p_Y * p_Texture->m_Width];
}
