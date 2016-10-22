// Star.cpp //
#include "Star.hpp"

Star::Star(string keyname) : Object(keyname)
{
  direction = Vector(0, 1);
}

void Star::Update(float deltaTime)
{
  Object::Update(deltaTime);

  if(position.Y > ScreenHeight)
    Remove();
}
