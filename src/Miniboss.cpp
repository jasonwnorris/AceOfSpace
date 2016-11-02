// Miniboss.cpp

// STL Includes
#define _USE_MATH_DEFINES
#include <math.h>
// AOS Includes
#include "Miniboss.hpp"
#include "Bullet.hpp"
#include "Player.hpp"

Miniboss::Miniboss(const std::string& keyname) : Enemy(keyname)
{
  pointValue = MinibossPointValue;
  health = MinibossHealth;
  position = Vector(0, -ScreenHeight / 2);

  lastFired = 0.0f;
}

void Miniboss::Update(float deltaTime)
{
  Enemy::Update(deltaTime);

  lastFired += deltaTime;
  if (lastFired > MinibossFireDelay)
    FireBullet();
}

void Miniboss::RemoveOffScreen()
{
  SDL_Rect screenBounds = {-ScreenWidth, -ScreenHeight, ScreenWidth * 3, ScreenHeight * 3};
  SDL_Rect objectBounds = GetBounds();

  if (SDL_HasIntersection(&screenBounds, &objectBounds) == SDL_FALSE)
  {
    Remove();
  }
}

// fire bullets in an octagon shape pattern
void Miniboss::FireBullet()
{
  for (int i = 0; i < 8; i++)
  {
    Bullet* bullet = new Bullet("NeonCross");
    bullet->position = position;
    bullet->direction = Vector::CalculateDirection(static_cast<float>(i * (M_PI / 4.0f) + (M_PI / 8.0f)));
    bullet->speed = 150.0f;
    bullet->CollisionList = &PlayerShip::PlayerShipList;
  }

  lastFired = 0.0f;
}
