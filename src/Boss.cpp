// Boss.cpp

// AOS Includes
#include "Boss.hpp"
#include "Sound.hpp"

Boss Boss::FinalBoss;

Boss::Boss()
{
  m_Boss = nullptr;
  m_IsSpawned = false;
  m_IsKilled = false;
}

void Boss::RemoveBoss()
{
  FinalBoss.m_Boss = nullptr;
  FinalBoss.m_IsSpawned = false;
  FinalBoss.m_IsKilled = false;
}

void Boss::SpawnBoss()
{
  FinalBoss.m_Boss = new BossEnemy("Boss");
  FinalBoss.m_IsSpawned = true;
  Sound::PlaySound("Boss");
}

void Boss::DestroyBoss()
{
  FinalBoss.m_Boss = nullptr;
  FinalBoss.m_IsKilled = true;
}

// BossEnemy.cpp

// AOS Includes
#include "Bullet.hpp"
#include "Player.hpp"

BossEnemy::BossEnemy(const std::string& p_Keyname) : Enemy(p_Keyname)
{
  m_PointValue = c_BossPointValue;

  m_Position = Vector2f(c_ScreenWidth / 2, -m_Sprite->m_Origin.Y);
  m_Direction = Vector2f::Down;
  m_Speed = c_BossSpeed;
  m_Health = c_BossHealth;

  m_ChildrenAngle = 0.0f;
  m_FireAngle = 0.0f;
  m_LastFired = 0.0f;

  m_LeftHand = new Miniboss("LeftHand");
  m_RightHand = new Miniboss("RightHand");
}

void BossEnemy::Update(float p_DeltaTime)
{
  Enemy::Update(p_DeltaTime);

  UpdateChildren();

  if (m_Direction.X < 0)
  {
    if (m_Position.X < 300)
    {
      m_Direction = Vector2f::Right;
    }
  }
  else if (m_Direction.X > 0)
  {
    if (m_Position.X > c_ScreenWidth - 300)
    {
      m_Direction = Vector2f::Left;
    }
  }
  else
  {
    if (m_Position.Y > c_ScreenHeight / 3)
    {
      if (rand() % 2 == 0)
      {
        m_Direction = Vector2f::Right;
      }
      else
      {
        m_Direction = Vector2f::Left;
      }
    }
  }

  m_ChildrenAngle += c_BossChildrenRotation;

  float difficulty = (m_Health < c_BossHealth / 2) ? 2.0f : 1.0f;
  m_FireAngle += c_BossFireRotation * difficulty;
  m_LastFired += p_DeltaTime * difficulty;

  if (m_LastFired > c_BossFireDelay)
  {
    FireBullet();
  }
}

void BossEnemy::UpdateChildren()
{
  if (m_LeftHand != nullptr)
  {
    if (m_LeftHand->m_Health > 0)
    {
      m_LeftHand->m_Position = m_Position + Vector2f::Left * 200.0f + Vector2f::Down * 75.0f + Vector2f::CalculateDirection(-m_ChildrenAngle) * 25.0f;
    }
    else
    {
      m_LeftHand = nullptr;
    }
  }

  if (m_RightHand != nullptr)
  {
    if (m_RightHand->m_Health > 0)
    {
      m_RightHand->m_Position = m_Position + Vector2f::Right * 200.0f + Vector2f::Down * 75.0f + Vector2f::CalculateDirection(m_ChildrenAngle) * -25.0f;
    }
    else
    {
      m_RightHand = nullptr;
    }
  }
}

void BossEnemy::RemoveOffScreen()
{
  SDL_Rect screenBounds = { -c_ScreenWidth, -c_ScreenHeight, c_ScreenWidth * 3, c_ScreenHeight * 3 };
  SDL_Rect objectBounds = GetBounds();

  if (SDL_HasIntersection(&screenBounds, &objectBounds) == SDL_FALSE)
  {
    Remove();
  }
}

void BossEnemy::Remove()
{
  Boss::DestroyBoss();

  Enemy::Remove();
}

void BossEnemy::FireBullet()
{
  Bullet* bullet = new Bullet("NeonOrb");
  bullet->m_Position = m_Position;
  bullet->m_Direction = Vector2f::CalculateDirection(m_FireAngle);
  bullet->m_Speed = 100.0f;
  bullet->CollisionList = &PlayerShip::PlayerShipList;

  m_LastFired = 0.0f;
}
