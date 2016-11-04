// Enemy.cpp

// STL Includes
#include <algorithm>
// AOS Includes
#include "Enemy.hpp"
#include "Player.hpp"
#include "Powerup.hpp"

std::vector<GameObject*> Enemy::EnemyList;

Enemy::Enemy(const std::string& p_Keyname) : GameObject(p_Keyname)
{
  m_Direction = Vector2f::Down;
  m_ExplosionKeyname = "Explosion";

  EnemyList.push_back(this);
}

Enemy::~Enemy()
{
}

void Enemy::RemoveKilled()
{
  EnemyList.erase(std::remove_if(EnemyList.begin(), EnemyList.end(), [](GameObject* p_GameObject) { return p_GameObject->IsDead(); }), EnemyList.end());
}

void Enemy::RemoveAll()
{
  EnemyList.clear();
}

void Enemy::Explode()
{
  GameObject::Explode();

  Player::AwardPoints(m_PointValue);

  DropItem();
}

void Enemy::DropItem()
{
  // 20% drop chance
  if (rand() % 5 == 0)
  {
    int dropType = rand() % 5;
    Item* item = nullptr;

    switch (dropType)
    {
      case 0:
        item = new Powerup("ItemHealth");
        break;
      case 1:
        item = new Powerup("ItemSpeed");
        break;
      case 2:
        item = new Powerup("ItemMissiles");
        break;
      case 3:
        item = new Powerup("ItemFireball");
        break;
      case 4:
        item = new Powerup("ItemPlasma");
        break;
    }

    item->SetPosition(m_Position);
  }
}
