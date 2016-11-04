// TargetShooter.cpp

// AOS Includes
#include "TargetShooter.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

TargetShooter::TargetShooter(const std::string& p_Keyname) : Enemy(p_Keyname)
{
  m_PointValue = TargetShooterPointValue;
  m_Health = TargetShooterHealth;
  m_Speed = TargetShooterSpeed;
  m_Target = nullptr;
  m_TargetDirection = Vector2f::Zero;
  m_LastFired = 0.0f;
}

void TargetShooter::Update(float p_DeltaTime)
{
  if (m_Target == nullptr || m_Target->m_IsDead)
  {
    m_Target = PickRandomObject(&PlayerShip::PlayerShipList);
  }

  if (m_Target != nullptr)
  {
    m_TargetDirection = m_Target->m_Position - m_Position;
    m_TargetDirection.Normalize();
  }
  else
  {
    m_TargetDirection = Vector2f::Down;
  }

  Enemy::Update(p_DeltaTime);

  m_LastFired += p_DeltaTime;
  if (m_LastFired > TargetShooterFireDelay)
  {
    FireBullet();
  }
}

void TargetShooter::FireBullet()
{
  Bullet* bullet = new Bullet("Slime");
  bullet->m_Position = m_Position;
  bullet->m_Direction = m_TargetDirection;
  bullet->CollisionList = &PlayerShip::PlayerShipList;

  m_LastFired = 0.0f;
}
