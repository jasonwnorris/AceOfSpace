// Star.cpp

// AOS Includes
#include "Star.hpp"

Star::Star(std::string keyname) : Object(keyname)
{
  direction = Vector(0, 1);
}

void Star::Update(float deltaTime)
{
  Object::Update(deltaTime);

  if (position.Y > ScreenHeight)
  {
    Remove();
  }
}
