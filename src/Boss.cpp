// Boss.cpp

// AOS Includes
#include "Boss.hpp"
#include "Sound.hpp"

Boss Boss::FinalBoss;

Boss::Boss()
{
  m_BossEnemy = nullptr;
  m_IsSpawned = false;
  m_IsKilled = false;
}

const BossEnemy* Boss::GetBossEnemy() const
{
  return m_BossEnemy;
}

bool Boss::IsSpawned() const
{
  return m_IsSpawned;
}

bool Boss::IsKilled() const
{
  return m_IsKilled;
}

void Boss::RemoveBoss()
{
  FinalBoss.m_BossEnemy = nullptr;
  FinalBoss.m_IsSpawned = false;
  FinalBoss.m_IsKilled = false;
}

void Boss::SpawnBoss()
{
  FinalBoss.m_BossEnemy = new BossEnemy("Boss");
  FinalBoss.m_IsSpawned = true;
  Sound::PlaySound("Boss");
}

void Boss::DestroyBoss()
{
  FinalBoss.m_BossEnemy = nullptr;
  FinalBoss.m_IsKilled = true;
}
