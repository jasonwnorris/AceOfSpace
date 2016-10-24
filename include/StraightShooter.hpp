// StraightShooter.hpp

#ifndef __STRAIGHTSHOOTER_HPP__
#define __STRAIGHTSHOOTER_HPP__

#include "Enemy.hpp"

class StraightShooter : public Enemy
{
  public:
    StraightShooter(std::string keyname);

    virtual void Update(float deltaTime);

  private:
    void FireBullet();

    float lastFired;
};

#endif
