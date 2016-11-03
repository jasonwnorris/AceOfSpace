// Missile.cpp

// AOS Includes
#include "Missile.hpp"

Missile::Missile(const std::string& keyname) : Projectile(keyname)
{
  speed = MissileSpeed;
  health = MissileHealth;
  target = nullptr;
}

// point the missile at its target, but very slowly
void Missile::Update(float deltaTime)
{
  if (target == nullptr || target->dead)
  {
    target = PickRandomObject(CollisionList);
  }

  if (target != nullptr)
  {
    Vector2f targetDirection = target->position - position;
    targetDirection.Normalize();
    direction += targetDirection * MissileHomingStrength;
  }

  Projectile::Update(deltaTime);
}

// give the missile some space to go offscreen and fly back on
void Missile::RemoveOffScreen()
{
  SDL_Rect screenBounds = {-ScreenWidth / 2, -ScreenHeight / 2, ScreenWidth * 2, ScreenHeight * 2};
  SDL_Rect objectBounds = GetBounds();

  if (SDL_HasIntersection(&screenBounds, &objectBounds) == SDL_FALSE)
  {
    Remove();
  }
}
