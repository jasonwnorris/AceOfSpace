// Star.cpp

// AOS Includes
#include "Star.hpp"

Star::Star(const std::string& keyname) : Object(keyname)
{
  m_Direction = Vector2f::Down;
}

void Star::Update(float deltaTime)
{
  Object::Update(deltaTime);

  if (m_Position.Y > ScreenHeight)
  {
    Remove();
  }
}
