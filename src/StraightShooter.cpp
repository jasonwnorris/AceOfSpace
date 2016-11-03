// StraightShooter.cpp

// AOS Includes
#include "StraightShooter.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

StraightShooter::StraightShooter(const std::string& keyname) : Enemy(keyname)
{
  pointValue = StraightShooterPointValue;
  health = StraightShooterHealth;
  speed = StraightShooterSpeed;
  lastFired = 0.0f;
}

void StraightShooter::Update(float deltaTime)
{
  Enemy::Update(deltaTime);

  lastFired += deltaTime;
  if (lastFired > StraightShooterFireDelay)
  {
    FireBullet();
  }
}

void StraightShooter::FireBullet()
{
  Bullet* bullet = new Bullet("Needle");
  bullet->position = position + Vector2f(0.0f, 58.0f);
  bullet->direction = Vector2f(0, 1);
  bullet->CollisionList = &PlayerShip::PlayerShipList;

  lastFired = 0.0f;
}
