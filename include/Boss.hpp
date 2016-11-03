// Boss.hpp

#ifndef __BOSS_HPP__
#define __BOSS_HPP__

// AOS Includes
#include "Enemy.hpp"
#include "Miniboss.hpp"

class BossEnemy : public Enemy
{
  public:
    BossEnemy(const std::string& keyname);

    void Update(float deltaTime);
    void UpdateChildren();

    void RemoveOffScreen();
    void Remove();

  private:
    void FireBullet();

    Miniboss* m_LeftHand;
    Miniboss* m_RightHand;
    float m_ChildrenAngle;
    float m_FireAngle;
    float m_LastFired;
};

class Boss
{
  public:
    Boss();

    static Boss FinalBoss;

    static void RemoveBoss();
    static void SpawnBoss();
    static void DestroyBoss();

    BossEnemy* m_Boss;
    bool m_IsSpawned;
    bool m_IsKilled;
};

#endif
