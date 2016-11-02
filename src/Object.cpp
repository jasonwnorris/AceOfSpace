// Object.cpp

// AOS Includes
#include "Object.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

std::vector<Object*> Object::ObjectList;
std::vector<Object*> Object::ObjectAddList;

Object::Object(const std::string& keyname)
{
  sprite = new Sprite(keyname);
  position = Vector(0, 0);
  direction = Vector(0, 0);
  speed = 0.0f;
  dead = false;

  ObjectAddList.push_back(this);
}

Object::~Object()
{
  delete sprite;
}

// objects can't be removed or added to a std::vector during iteration
// so we do that afterwards
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
  sprite->Update(deltaTime);
  direction.Normalize();
  Move(direction * speed * deltaTime);
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
  sprite->Render(renderer, position);
}

// we want to add objects during the main iteration
// so we temporarily store them in an auxiliary std::vector
// then push them on after we're done updating
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
    if ((*Iter)->dead)
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

// make an object as dead so we can remove it after we finish updating
void Object::Remove()
{
  dead = true;
}

void Object::Move(Vector amount)
{
  position += amount;
}

// return an SDL_Rect surrounding our object
SDL_Rect Object::GetBounds()
{
  SDL_Rect bounds;
  bounds.x = (Sint16)(position.X - sprite->origin.X);
  bounds.y = (Sint16)(position.Y - sprite->origin.Y);
  bounds.w = (Sint16)(sprite->texture->tileWidth);
  bounds.h = (Sint16)(sprite->texture->tileWidth);

  return bounds;
}

// helps with pixel collision, this is a little tricky
// this returns an SDL_Rect that covers the area of the frame intersecting with the provided "rect"
SDL_Rect Object::NormalizeBounds(const SDL_Rect& rect)
{
  SDL_Rect normalizeRect;
  normalizeRect.x = (Sint16)(rect.x + sprite->GetFrameBounds().x + sprite->origin.X - position.X);
  normalizeRect.y = (Sint16)(rect.y + sprite->GetFrameBounds().y + sprite->origin.Y - position.Y);
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

  Texture* textureA = objectA->sprite->texture;
  Texture* textureB = objectB->sprite->texture;

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
  return texture->solidity[x + y * texture->width];
}
