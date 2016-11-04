// Miniboss.cpp

// STL Includes
#define _USE_MATH_DEFINES
#include <math.h>
// AOS Includes
#include "Miniboss.hpp"
#include "Bullet.hpp"
#include "Player.hpp"

Miniboss::Miniboss(const std::string& p_Keyname) : Enemy(p_Keyname)
{
  m_PointValue = c_MinibossPointValue;
  m_Health = c_MinibossHealth;
  m_Position = Vector2f::Up * c_ScreenHeight / 2.0f;
  m_LastFired = 0.0f;
}

void Miniboss::Update(float p_DeltaTime)
{
  Enemy::Update(p_DeltaTime);

  m_LastFired += p_DeltaTime;
  if (m_LastFired > c_MinibossFireDelay)
  {
    FireBullet();
  }
}

void Miniboss::RemoveOffScreen()
{
  SDL_Rect screenBounds = { -c_ScreenWidth, -c_ScreenHeight, c_ScreenWidth * 3, c_ScreenHeight * 3 };
  SDL_Rect objectBounds = GetBounds();

  if (SDL_HasIntersection(&screenBounds, &objectBounds) == SDL_FALSE)
  {
    Remove();
  }
}

void Miniboss::FireBullet()
{
  for (int i = 0; i < 8; i++)
  {
    Bullet* bullet = new Bullet("NeonCross");
    bullet->m_Position = m_Position;
    bullet->m_Direction = Vector2f::CalculateDirection(static_cast<float>(i * (M_PI / 4.0f) + (M_PI / 8.0f)));
    bullet->m_Speed = 150.0f;
    bullet->CollisionList = &PlayerShip::PlayerShipList;
  }

  m_LastFired = 0.0f;
}
