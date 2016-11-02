// Miniboss.hpp

#ifndef __MINIBOSS_HPP__
#define __MINIBOSS_HPP__

// AOS Includes
#include "Enemy.hpp"

class Miniboss : public Enemy
{
    public:
    Miniboss(std::string keyname);

    void Update(float deltaTime);

    void RemoveOffScreen();

  private:
    void FireBullet();

    float lastFired;
};

#endif
