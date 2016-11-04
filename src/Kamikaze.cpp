// Kamikaze.cpp

// AOS Includes
#include "Kamikaze.hpp"
#include "Player.hpp"

Kamikaze::Kamikaze(const std::string& p_Keyname) : Enemy(p_Keyname)
{
  m_PointValue = c_KamikazePointValue;
  m_Health = c_KamikazeHealth;
  m_Speed = c_KamikazeIdleSpeed;
  m_IdleDelay = c_KamikazeIdleDelay;
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
        m_Direction = target->GetPosition() - m_Position;
      }

      m_Speed = c_KamikazeAttackSpeed;
      m_HasFoundTarget = true;
    }
  }

  Enemy::Update(p_DeltaTime);
}
