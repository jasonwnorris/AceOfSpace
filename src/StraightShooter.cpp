// StraightShooter.cpp

// AOS Includes
#include "StraightShooter.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

StraightShooter::StraightShooter(const std::string& keyname) : Enemy(keyname)
{
  m_PointValue = StraightShooterPointValue;
  m_Health = StraightShooterHealth;
  m_Speed = StraightShooterSpeed;
  m_LastFired = 0.0f;
}

void StraightShooter::Update(float deltaTime)
{
  Enemy::Update(deltaTime);

  m_LastFired += deltaTime;
  if (m_LastFired > StraightShooterFireDelay)
  {
    FireBullet();
  }
}

void StraightShooter::FireBullet()
{
  Bullet* bullet = new Bullet("Needle");
  bullet->m_Position = m_Position + Vector2f::Down * 58.0f;
  bullet->m_Direction = Vector2f::Down;
  bullet->CollisionList = &PlayerShip::PlayerShipList;

  m_LastFired = 0.0f;
}
