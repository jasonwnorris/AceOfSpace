// StraightShooter.cpp //
#include "StraightShooter.hpp"

#include "Player.hpp"
#include "Bullet.hpp"

StraightShooter::StraightShooter(std::string keyname) : Enemy(keyname)
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
  bullet->position = position + Vector(0, 58.0f);
  bullet->direction = Vector(0, 1);
  bullet->CollisionList = &PlayerShip::PlayerShipList;

  lastFired = 0.0f;
}
