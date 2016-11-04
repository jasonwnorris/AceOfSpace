// PlayerShip.cpp

// STL Includes
#include <sstream>
// AOS Includes
#include "Player.hpp"
#include "Sound.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Missile.hpp"
#include "Fireball.hpp"

std::vector<GameObject*> PlayerShip::PlayerShipList;

PlayerShip::PlayerShip(const std::string& p_Keyname) : GameObject(p_Keyname)
{
  m_Position = Vector2f(c_ScreenWidth / 2.0f, static_cast<float>(c_ScreenHeight - m_Sprite->m_Texture->m_TileHeight - c_PlayerSpawnOffset));
  m_Speed = c_PlayerSpeed;
  m_Health = c_PlayerHealth;
  m_ExplosionKeyname = "Explosion";
  m_WeaponType = WEAPON_BULLET;
  CollisionList = &Enemy::EnemyList;

  m_IsMovingUp = false;
  m_IsMovingDown = false;
  m_IsMovingLeft = false;
  m_IsMovingRight = false;
  m_IsShooting = false;
  m_LastFired = 0.0f;

  PlayerShipList.push_back(this);
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

  // Horizontally constraint sprite to screen.
  if (m_Position.X < m_Sprite->m_Origin.X)
  {
    m_Position.X = m_Sprite->m_Origin.X;
  }
  else if (m_Position.X > c_ScreenWidth - m_Sprite->m_Origin.X)
  {
    m_Position.X = c_ScreenWidth - m_Sprite->m_Origin.X;
  }

  // Vertically constraint sprite to screen.
  if (m_Position.Y < m_Sprite->m_Origin.Y)
  {
    m_Position.Y = m_Sprite->m_Origin.Y;
  }
  else if (m_Position.Y > c_ScreenHeight - m_Sprite->m_Origin.Y)
  {
    m_Position.Y = c_ScreenHeight - m_Sprite->m_Origin.Y;
  }
}

void PlayerShip::RemoveKilled()
{
  for (std::vector<GameObject*>::iterator Iter = PlayerShipList.begin(); Iter != PlayerShipList.end(); Iter += 0)
  {
    if ((*Iter)->m_IsDead)
    {
      Iter = PlayerShipList.erase(Iter);
    }
    else
    {
      ++Iter;
    }
  }
}

void PlayerShip::RemoveAll()
{
  for (std::vector<GameObject*>::iterator Iter = PlayerShipList.begin(); Iter != PlayerShipList.end(); Iter += 0)
  {
    Iter = PlayerShipList.erase(Iter);
  }
}

void PlayerShip::Remove()
{
  Player::DestroyPlayer(this);

  GameObject::Remove();
}

void PlayerShip::Collide(GameObject* p_GameObject)
{
  int objectHealth = p_GameObject->m_Health;
  p_GameObject->TakeDamage(m_Health);
  this->TakeDamage(objectHealth);
}

void PlayerShip::FireBullet()
{
  if (m_IsShooting)
  {
    if (m_WeaponType == WEAPON_BULLET)
    {
      if (m_LastFired > c_PlayerFireDelay)
      {
        for (int i = 0; i < 3; ++i)
        {
          Projectile* projectile = new Bullet("Bullet");
          projectile->m_Position = m_Position + Vector2f::Left * (1 - i) * 5.0f + Vector2f::Up * 20.0f;
          projectile->m_Direction = Vector2f::Up;
          projectile->CollisionList = &Enemy::EnemyList;
        }

        m_LastFired = 0.0f;
      }
    }
    else if (m_WeaponType == WEAPON_MISSILE || m_WeaponType == WEAPON_PLASMA)
    {
      if (m_LastFired > c_PlayerFireDelay)
      {
        int total = 5;
        for (int i = 0; i < total; ++i)
        {
          Projectile* projectile = nullptr;

          if (m_WeaponType == WEAPON_MISSILE)
          {
            projectile = new Missile("Missile");
          }
          else if (m_WeaponType == WEAPON_PLASMA)
          {
            projectile = new Bullet("Plasma");
          }

          projectile->m_Position = m_Position + Vector2f::Up * 20.0f;
          projectile->m_Direction = Vector2f::Right * (i - (total / 2)) / 10.0f + Vector2f::Up;
          projectile->CollisionList = &Enemy::EnemyList;
        }

        m_LastFired = 0.0f;
      }
    }
    else if (m_WeaponType == WEAPON_FIREBALL)
    {
      if (m_LastFired > c_FireballFireDelay)
      {
        Projectile* projectile = new Fireball("Flames");
        projectile->m_Position = m_Position + Vector2f::Up * 28.0f;
        projectile->m_Direction = Vector2f::Right * (rand() % 101 - 50) / 100.0f + Vector2f::Up;
        projectile->CollisionList = &Enemy::EnemyList;

        m_LastFired = 0.0f;
      }
    }
  }
}
