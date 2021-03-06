// Missile.cpp

// AOS Includes
#include "Missile.hpp"

Missile::Missile(const std::string& p_Keyname) : Projectile(p_Keyname)
{
  m_Speed = c_MissileSpeed;
  m_Health = c_MissileHealth;
  m_Target = nullptr;
}

void Missile::Update(float p_DeltaTime)
{
  if (m_Target == nullptr || m_Target->IsDead())
  {
    m_Target = PickRandomObject(m_CollisionList);
  }

  if (m_Target != nullptr)
  {
    Vector2f m_TargetDirection = m_Target->GetPosition() - m_Position;
    m_TargetDirection.Normalize();
    m_Direction += m_TargetDirection * c_MissileHomingStrength;
  }

  Projectile::Update(p_DeltaTime);
}

void Missile::RemoveOffScreen()
{
  SDL_Rect screenBounds = { -c_HalfScreenWidth, -c_HalfScreenHeight, c_ScreenWidth * 2, c_ScreenHeight * 2 };
  SDL_Rect objectBounds = GetBounds();

  if (SDL_HasIntersection(&screenBounds, &objectBounds) == SDL_FALSE)
  {
    Remove();
  }
}
