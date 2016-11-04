// PlayerShip.cpp

// STL Includes
#include <algorithm>
#include <sstream>
// AOS Includes
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Missile.hpp"
#include "Fireball.hpp"
#include "WeaponType.hpp"

std::vector<GameObject*> PlayerShip::PlayerShipList;

PlayerShip::PlayerShip(const std::string& p_Keyname) : GameObject(p_Keyname)
{
  m_Position = Vector2f(c_HalfScreenWidth, c_ScreenHeight - m_Sprite->GetTexture()->GetTileHeight() - c_PlayerSpawnOffset);
  m_Speed = c_PlayerSpeed;
  m_Health = c_PlayerHealth;
  m_ExplosionKeyname = "Explosion";
  m_WeaponType = WEAPON_BULLET;
  m_CollisionList = &Enemy::EnemyList;

  m_IsMovingUp = false;
  m_IsMovingDown = false;
  m_IsMovingLeft = false;
  m_IsMovingRight = false;
  m_IsShooting = false;
  m_LastFired = 0.0f;

  PlayerShipList.push_back(this);
}

void PlayerShip::SetMovingUp(bool p_IsMovingUp)
{
  m_IsMovingUp = p_IsMovingUp;
}

void PlayerShip::SetMovingDown(bool p_IsMovingDown)
{
  m_IsMovingDown = p_IsMovingDown;
}

void PlayerShip::SetMovingLeft(bool p_IsMovingLeft)
{
  m_IsMovingLeft = p_IsMovingLeft;
}

void PlayerShip::SetMovingRight(bool p_IsMovingRight)
{
  m_IsMovingRight = p_IsMovingRight;
}

void PlayerShip::SetShooting(bool p_IsShooting)
{
  m_IsShooting = p_IsShooting;
}

void PlayerShip::Update(float p_DeltaTime)
{
  m_Direction = Vector2f::Zero;

  if (m_IsMovingUp)
  {
    m_Direction += Vector2f::Up;
  }
  if (m_IsMovingDown)
  {
    m_Direction += Vector2f::Down;
  }
  if (m_IsMovingLeft)
  {
    m_Direction += Vector2f::Left;
  }
  if (m_IsMovingRight)
  {
    m_Direction += Vector2f::Right;
  }

  m_LastFired += p_DeltaTime;
  FireBullet();

  GameObject::Update(p_DeltaTime);

  const Vector2f& origin = m_Sprite->GetOrigin();

  // Horizontally constraint sprite to screen.
  if (m_Position.X < origin.X)
  {
    m_Position.X = origin.X;
  }
  else if (m_Position.X > c_ScreenWidth - origin.X)
  {
    m_Position.X = c_ScreenWidth - origin.X;
  }

  // Vertically constraint sprite to screen.
  if (m_Position.Y < origin.Y)
  {
    m_Position.Y = origin.Y;
  }
  else if (m_Position.Y > c_ScreenHeight - origin.Y)
  {
    m_Position.Y = c_ScreenHeight - origin.Y;
  }
}

void PlayerShip::RemoveKilled()
{
  PlayerShipList.erase(std::remove_if(PlayerShipList.begin(), PlayerShipList.end(), [](GameObject* p_GameObject) { return p_GameObject->IsDead(); }), PlayerShipList.end());
}

void PlayerShip::RemoveAll()
{
  PlayerShipList.clear();
}

void PlayerShip::Remove()
{
  Player::DestroyPlayer(this);

  GameObject::Remove();
}

void PlayerShip::Collide(GameObject* p_GameObject)
{
  int objectHealth = p_GameObject->GetHealth();
  p_GameObject->TakeDamage(m_Health);
  TakeDamage(objectHealth);
}

void PlayerShip::FireBullet()
{
  if (m_IsShooting)
  {
    switch (m_WeaponType)
    {
      case WEAPON_BULLET:
        if (m_LastFired > c_PlayerFireDelay)
        {
          for (int i = 0; i < 3; ++i)
          {
            Projectile* projectile = new Bullet("Bullet");
            projectile->SetPosition(m_Position + Vector2f::Left * (1 - i) * 5.0f + Vector2f::Up * 20.0f);
            projectile->SetDirection(Vector2f::Up);
            projectile->SetCollisionList(&Enemy::EnemyList);
          }

          m_LastFired = 0.0f;
        }
        break;
      case WEAPON_MISSILE:
      case WEAPON_PLASMA:
        if (m_LastFired > c_PlayerFireDelay)
        {
          int total = 5;
          for (int i = 0; i < total; ++i)
          {
            Projectile* projectile = nullptr;

            switch (m_WeaponType)
            {
              case WEAPON_MISSILE:
                projectile = new Missile("Missile");
                break;
              case WEAPON_PLASMA:
                projectile = new Bullet("Plasma");
                break;
            }

            projectile->SetPosition(m_Position + Vector2f::Up * 20.0f);
            projectile->SetDirection(Vector2f::Right * (i - (total / 2)) / 10.0f + Vector2f::Up);
            projectile->SetCollisionList(&Enemy::EnemyList);
          }

          m_LastFired = 0.0f;
        }
        break;
      case WEAPON_FIREBALL:
        if (m_LastFired > c_FireballFireDelay)
        {
          Projectile* projectile = new Fireball("Flames");
          projectile->SetPosition(m_Position + Vector2f::Up * 28.0f);
          projectile->SetDirection(Vector2f::Right * (rand() % 101 - 50) / 100.0f + Vector2f::Up);
          projectile->SetCollisionList(&Enemy::EnemyList);

          m_LastFired = 0.0f;
        }
        break;
    }
  }
}
