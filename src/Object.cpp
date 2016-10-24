// Object.cpp //
#include "Object.hpp"

#include "Player.hpp"
#include "Enemy.hpp"

std::vector<Object*> Object::ObjectList;
std::vector<Object*> Object::ObjectAddList;

Object::Object(std::string keyname)
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

// checks to see if two SDL_Rects intersect
// returns the colliding area if true, or an empty one if false
SDL_Rect Object::Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB)
{
  int x1 = Maximum(boundsA.x, boundsB.x);
  int y1 = Maximum(boundsA.y, boundsB.y);
  int x2 = Minimum(boundsA.x + boundsA.w, boundsB.x + boundsB.w);
  int y2 = Minimum(boundsA.y + boundsA.h, boundsB.y + boundsB.h);

  int width = x2 - x1;
  int height = y2 - y1;

  if (width > 0 && height > 0)
  {
    SDL_Rect intersect = {x1, y1, width, height};
    return intersect;
  }
  else
  {
    SDL_Rect intersect = {0, 0, 0, 0};
    return intersect;
  }
}

// checks bounding box collision first, if true, it continues on
// don't do per pixel collision every time, YOUR PROCESSOR WILL CRY!
// next, it grabs the area of the surface that will actually need to be checked
// then sees if the pixels in the same (x,y) are fully opaque (alpha == 255)
bool Object::CheckCollision(Object* objectA, Object* objectB)
{
  SDL_Rect collisionRect = Intersection(objectA->GetBounds(), objectB->GetBounds());

  if (collisionRect.w == 0 && collisionRect.h == 0)
  {
    return false;
  }

  //SDL_Rect normalA = objectA->NormalizeBounds(collisionRect);
  //SDL_Rect normalB = objectB->NormalizeBounds(collisionRect);

  //SDL_Surface* surfaceA = objectA->sprite->texture->textures[0];
 // SDL_Surface* surfaceB = objectB->sprite->texture->textures[0];

  //for (int y = 0; y <= collisionRect.h; ++y)
  //  for (int x = 0; x <= collisionRect.w; ++x)
  //    if (GetAlphaXY(surfaceA, normalA.x + x, normalA.y + y) && GetAlphaXY(surfaceB, normalB.x + x, normalB.y + y))
  //      return true;

  return false;
}

// helper function to find the alpha on a surface with a give (x,y)
bool Object::GetAlphaXY(SDL_Surface* surface, int x, int y)
{
  int bpp = surface->format->BytesPerPixel;
  Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
  Uint32 pixelColor;

  switch(bpp)
  {
    case(1):
      pixelColor = *p;
      break;
    case(2):
      pixelColor = *(Uint16*)p;
      break;
    case(3):
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        pixelColor = p[0] << 16 | p[1] << 8 | p[2];
      else
        pixelColor = p[0] | p[1] << 8 | p[2] << 16;
      break;
    case(4):
      pixelColor = *(Uint32*)p;
      break;
  }

  Uint8 red, green, blue, alpha;
  SDL_GetRGBA(pixelColor, surface->format, &red, &green, &blue, &alpha);

  return alpha == 255;
}
