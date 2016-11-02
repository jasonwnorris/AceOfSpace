// Enemy.hpp

#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

// AOS Includes
#include "GameObject.hpp"

class Enemy : public GameObject
{
  public:
    Enemy(const std::string& keyname);
    virtual ~Enemy();

    static std::vector<GameObject*> EnemyList;

    static void RemoveKilled();
    static void RemoveAll();

    void Explode();

  protected:
    int pointValue;

  private:
    void DropItem();
};

#endif
