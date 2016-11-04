// Kamikaze.cpp

// AOS Includes
#include "Kamikaze.hpp"
#include "Player.hpp"

Kamikaze::Kamikaze(const std::string& p_Keyname) : Enemy(p_Keyname)
{
  m_PointValue = KamikazePointValue;
  m_Health = KamikazeHealth;
  m_Speed = KamikazeIdleSpeed;
  m_IdleDelay = KamikazeIdleDelay;
  m_HasFoundTarget = false;
}

void Kamikaze::Update(float p_DeltaTime)
{
  if (!m_HasFoundTarget)
  {
    m_IdleDelay -= p_DeltaTime;
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

  Enemy::Update(p_DeltaTime);
}
