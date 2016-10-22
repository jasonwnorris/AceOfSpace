// Miniboss.h //
#ifndef MINIBOSS_H
#define MINIBOSS_H

#include "Enemy.h"

class Miniboss : public Enemy
{
    public:
    Miniboss(string keyname);

    void Update(float deltaTime);

    void RemoveOffScreen();

  private:
    void FireBullet();
    
    float lastFired;
};

#endif
