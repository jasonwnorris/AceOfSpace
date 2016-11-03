// Kamikaze.hpp

#ifndef __KAMIKAZE_HPP__
#define __KAMIKAZE_HPP__

// AOS Includes
#include "Enemy.hpp"

class Kamikaze : public Enemy
{
  public:
    Kamikaze(const std::string& keyname);

    void Update(float deltaTime);

  private:
    float m_IdleDelay;
    bool m_HasFoundTarget;
};

#endif
