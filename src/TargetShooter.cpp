// TargetShooter.cpp

// AOS Includes
#include "TargetShooter.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

TargetShooter::TargetShooter(const std::string& keyname) : Enemy(keyname)
{
  pointValue = TargetShooterPointValue;
  health = TargetShooterHealth;
  speed = TargetShooterSpeed;
  target = nullptr;
  targetDirection = Vector(0, 0);
  lastFired = 0.0f;
}

void TargetShooter::Update(float deltaTime)
{
  if (target == nullptr || target->dead)
  {
    target = PickRandomObject(&PlayerShip::PlayerShipList);
  }

  if (target != nullptr)
  {
    targetDirection = target->position - position;
    targetDirection.Normalize();
  }
  else
  {
    targetDirection = Vector(0, 1);
  }

  Enemy::Update(deltaTime);

  lastFired += deltaTime;
  if (lastFired > TargetShooterFireDelay)
  {
    FireBullet();
  }
}

void TargetShooter::FireBullet()
{
  Bullet* bullet = new Bullet("Slime");
  bullet->position = position;
  bullet->direction = targetDirection;
  bullet->CollisionList = &PlayerShip::PlayerShipList;

  lastFired = 0.0f;
}
