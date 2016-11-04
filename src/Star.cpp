// Star.cpp

// AOS Includes
#include "Star.hpp"

Star::Star(const std::string& p_Keyname) : Object(p_Keyname)
{
  m_Direction = Vector2f::Down;
}

void Star::Update(float p_DeltaTime)
{
  Object::Update(p_DeltaTime);

  if (m_Position.Y > c_ScreenHeight)
  {
    Remove();
  }
}
