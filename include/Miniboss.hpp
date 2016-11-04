// Miniboss.hpp

#ifndef __MINIBOSS_HPP__
#define __MINIBOSS_HPP__

// AOS Includes
#include "Enemy.hpp"

class Miniboss : public Enemy
{
    public:
    Miniboss(const std::string& p_Keyname);

    void Update(float p_DeltaTime);

    void RemoveOffScreen();

  private:
    void FireBullet();

    float m_LastFired;
};

#endif
