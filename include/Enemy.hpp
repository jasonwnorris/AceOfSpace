// Enemy.hpp

#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

#include "GameObject.hpp"

class Enemy : public GameObject
{
  public:
    Enemy(string keyname);

    static vector<GameObject*> EnemyList;

    static void RemoveKilled();
    static void RemoveAll();

    void Explode();

  protected:
    int pointValue;

  private:
    void DropItem();
};

#endif
