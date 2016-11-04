// StraightShooter.hpp

#ifndef __STRAIGHTSHOOTER_HPP__
#define __STRAIGHTSHOOTER_HPP__

// AOS Includes
#include "Enemy.hpp"

class StraightShooter : public Enemy
{
  public:
    StraightShooter(const std::string& p_Keyname);

    virtual void Update(float p_DeltaTime);

  private:
    void FireBullet();

    float m_LastFired;
};

#endif
