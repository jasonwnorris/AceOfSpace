// TargetShooter.hpp

#ifndef __TARGETSHOOTER_HPP__
#define __TARGETSHOOTER_HPP__

#include "Enemy.hpp"

class TargetShooter : public Enemy
{
  public:
    TargetShooter(std::string keyname);

    virtual void Update(float deltaTime);

  private:
    void FireBullet();

    GameObject* target;
    Vector targetDirection;
    float lastFired;
};

#endif
