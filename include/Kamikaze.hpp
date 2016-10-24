// Kamikaze.hpp

#ifndef __KAMIKAZE_HPP__
#define __KAMIKAZE_HPP__

#include "Enemy.hpp"

class Kamikaze : public Enemy
{
  public:
    Kamikaze(std::string keyname);

    void Update(float deltaTime);

  private:
    float idleDelay;
    bool foundTarget;
};

#endif
