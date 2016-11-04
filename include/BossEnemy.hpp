// BossEnemy.hpp

#ifndef __BOSSENEMY_HPP__
#define __BOSSENEMY_HPP__

// AOS Includes
#include "Miniboss.hpp"

class BossEnemy : public Enemy
{
  public:
    BossEnemy(const std::string& p_Keyname);

    void Update(float p_DeltaTime);
    void UpdateChildren();

    void RemoveOffScreen();
    void Remove();

  private:
    void FireBullet();

    Miniboss* m_LeftHand;
    Miniboss* m_RightHand;
    float m_ChildrenAngle;
    float m_FireAngle;
    float m_LastFired;
};

#endif
