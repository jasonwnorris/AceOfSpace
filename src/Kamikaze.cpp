// Kamikaze.cpp

// AOS Includes
#include "Kamikaze.hpp"
#include "Player.hpp"

Kamikaze::Kamikaze(const std::string& keyname) : Enemy(keyname)
{
  m_PointValue = KamikazePointValue;
  m_Health = KamikazeHealth;
  m_Speed = KamikazeIdleSpeed;
  m_IdleDelay = KamikazeIdleDelay;
  m_HasFoundTarget = false;
}

void Kamikaze::Update(float deltaTime)
{
  if (!m_HasFoundTarget)
  {
    m_IdleDelay -= deltaTime;

    if (m_IdleDelay <= 0.0f)
    {
      GameObject* target = PickRandomObject(&PlayerShip::PlayerShipList);
      if (target != nullptr)
      {
        m_Direction = target->m_Position - m_Position;
      }

      m_Speed = KamikazeAttackSpeed;
      m_HasFoundTarget = true;
    }
  }

  Enemy::Update(deltaTime);
}
