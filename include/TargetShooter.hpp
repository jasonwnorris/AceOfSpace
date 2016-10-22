// TargetShooter.h //
#ifndef TARGET_SHOOTER_H
#define TARGET_SHOOTER_H

#include "Enemy.hpp"

class TargetShooter : public Enemy
{
  public:
    TargetShooter(string keyname);

    virtual void Update(float deltaTime);

    private:
    void FireBullet();

    GameObject* target;
    Vector targetDirection;
    
    float lastFired;
};

#endif
