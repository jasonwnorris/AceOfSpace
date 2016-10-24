// Boss.hpp

#ifndef __BOSS_HPP__
#define __BOSS_HPP__

#include "Enemy.hpp"
#include "Miniboss.hpp"

class BossEnemy : public Enemy
{
  public:
    BossEnemy(std::string keyname);

    void Update(float deltaTime);
    void UpdateChildren();

    void RemoveOffScreen();
    void Remove();

  private:
    void FireBullet();

    Miniboss* leftHand;
    Miniboss* rightHand;

    float childrenAngle;
    float fireAngle;
    float lastFired;
};

class Boss
{
  public:
    Boss();

    static Boss FinalBoss;

    static void RemoveBoss();
    static void SpawnBoss();
    static void DestroyBoss();

    BossEnemy* boss;
    bool spawned;
    bool killed;
};

#endif
