// Missile.cpp

// AOS Includes
#include "Missile.hpp"

Missile::Missile(const std::string& p_Keyname) : Projectile(p_Keyname)
{
  m_Speed = MissileSpeed;
  m_Health = MissileHealth;
  m_Target = nullptr;
}

void Missile::Update(float p_DeltaTime)
{
  if (m_Target == nullptr || m_Target->m_IsDead)
  {
    m_Target = PickRandomObject(CollisionList);
  }

  if (m_Target != nullptr)
  {
    Vector2f m_TargetDirection = m_Target->m_Position - m_Position;
    m_TargetDirection.Normalize();
    m_Direction += m_TargetDirection * MissileHomingStrength;
  }

  Projectile::Update(p_DeltaTime);
}

void Missile::RemoveOffScreen()
{
  SDL_Rect screenBounds = { -ScreenWidth / 2, -ScreenHeight / 2, ScreenWidth * 2, ScreenHeight * 2 };
  SDL_Rect objectBounds = GetBounds();

  if (SDL_HasIntersection(&screenBounds, &objectBounds) == SDL_FALSE)
  {
    Remove();
  }
}
