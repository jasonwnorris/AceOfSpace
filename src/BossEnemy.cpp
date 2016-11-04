// BossEnemy.cpp

// AOS Includes
#include "Boss.hpp"
#include "Bullet.hpp"
#include "PlayerShip.hpp"

BossEnemy::BossEnemy(const std::string& p_Keyname) : Enemy(p_Keyname)
{
  m_PointValue = c_BossPointValue;

  m_Position = Vector2f(static_cast<float>(c_HalfScreenWidth), -m_Sprite->GetOrigin().Y);
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

  if (m_Direction.X < 0.0f)
  {
    if (m_Position.X < 300.0f)
    {
      m_Direction = Vector2f::Right;
    }
  }
  else if (m_Direction.X > 0.0f)
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
      m_Direction = (rand() % 2 == 0) ? Vector2f::Right : Vector2f::Left;
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
  bullet->SetPosition(m_Position);
  bullet->SetDirection(Vector2f::CalculateDirection(m_FireAngle));
  bullet->SetSpeed(100.0f);
  bullet->SetCollisionList(&PlayerShip::PlayerShipList);

  m_LastFired = 0.0f;
}

void BossEnemy::UpdateChildren()
{
  if (m_LeftHand != nullptr)
  {
    if (m_LeftHand->GetHealth() > 0)
    {
      m_LeftHand->SetPosition(m_Position + Vector2f::Left * 200.0f + Vector2f::Down * 75.0f + Vector2f::CalculateDirection(-m_ChildrenAngle) * 25.0f);
    }
    else
    {
      m_LeftHand = nullptr;
    }
  }

  if (m_RightHand != nullptr)
  {
    if (m_RightHand->GetHealth() > 0)
    {
      m_RightHand->SetPosition(m_Position + Vector2f::Right * 200.0f + Vector2f::Down * 75.0f + Vector2f::CalculateDirection(m_ChildrenAngle) * -25.0f);
    }
    else
    {
      m_RightHand = nullptr;
    }
  }
}
