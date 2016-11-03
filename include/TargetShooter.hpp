// TargetShooter.hpp

#ifndef __TARGETSHOOTER_HPP__
#define __TARGETSHOOTER_HPP__

// AOS Includes
#include "Enemy.hpp"

class TargetShooter : public Enemy
{
  public:
    TargetShooter(const std::string& keyname);

    virtual void Update(float deltaTime);

  private:
    void FireBullet();

    GameObject* target;
    Vector2f targetDirection;
    float lastFired;
};

#endif
