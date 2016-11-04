// Enemy.hpp

#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

// AOS Includes
#include "GameObject.hpp"

class Enemy : public GameObject
{
  public:
    Enemy(const std::string& p_Keyname);
    virtual ~Enemy();

    static std::vector<GameObject*> EnemyList;

    static void RemoveKilled();
    static void RemoveAll();

    void Explode();

  protected:
    int m_PointValue;

  private:
    void DropItem();
};

#endif
