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

    static void RemoveBoss();
    static void SpawnBoss();
    static void DestroyBoss();

    BossEnemy* m_BossEnemy;
    bool m_IsSpawned;
    bool m_IsKilled;
};

#endif
