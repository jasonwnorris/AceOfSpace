// StraightShooter.cpp

// AOS Includes
#include "StraightShooter.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

StraightShooter::StraightShooter(const std::string& p_Keyname) : Enemy(p_Keyname)
{
  m_PointValue = c_StraightShooterPointValue;
  m_Health = c_StraightShooterHealth;
  m_Speed = c_StraightShooterSpeed;
  m_LastFired = 0.0f;
}

void StraightShooter::Update(float p_DeltaTime)
{
  Enemy::Update(p_DeltaTime);

  m_LastFired += p_DeltaTime;
  if (m_LastFired > c_StraightShooterFireDelay)
  {
    FireBullet();
  }
}

void StraightShooter::FireBullet()
{
  Bullet* bullet = new Bullet("Needle");
  bullet->SetPosition(m_Position + Vector2f::Down * 58.0f);
  bullet->SetDirection(Vector2f::Down);
  bullet->SetCollisionList(&PlayerShip::PlayerShipList);

  m_LastFired = 0.0f;
}
