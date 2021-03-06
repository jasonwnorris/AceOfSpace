// Boss.hpp

#ifndef __BOSS_HPP__
#define __BOSS_HPP__

// AOS Includes
#include "BossEnemy.hpp"

class Boss
{
  public:
    Boss();

    static Boss FinalBoss;

    const BossEnemy* GetBossEnemy() const;
    bool IsSpawned() const;
    bool IsKilled() const;

    static void RemoveBoss();
    static void SpawnBoss();
    static void DestroyBoss();

  private:
    BossEnemy* m_BossEnemy;
    bool m_IsSpawned;
    bool m_IsKilled;
};

#endif
