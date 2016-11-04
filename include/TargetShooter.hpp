// TargetShooter.hpp

#ifndef __TARGETSHOOTER_HPP__
#define __TARGETSHOOTER_HPP__

// AOS Includes
#include "Enemy.hpp"

class TargetShooter : public Enemy
{
  public:
    TargetShooter(const std::string& p_Keyname);

    virtual void Update(float p_DeltaTime);

  private:
    void FireBullet();

    GameObject* m_Target;
    Vector2f m_TargetDirection;
    float m_LastFired;
};

#endif
