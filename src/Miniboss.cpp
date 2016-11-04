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
  m_Position = Vector2f::Up * c_HalfScreenHeight;
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
  float piOver4 = static_cast<float>(M_PI / 4.0f);
  float piOver8 = static_cast<float>(M_PI / 8.0f);

  for (int i = 0; i < 8; i++)
  {
    Bullet* bullet = new Bullet("NeonCross");
    bullet->SetPosition(m_Position);
    bullet->SetDirection(Vector2f::CalculateDirection(i * piOver4 + piOver8));
    bullet->SetSpeed(150.0f);
    bullet->SetCollisionList(&PlayerShip::PlayerShipList);
  }

  m_LastFired = 0.0f;
}
