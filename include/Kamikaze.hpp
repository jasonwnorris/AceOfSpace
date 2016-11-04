// Kamikaze.hpp

#ifndef __KAMIKAZE_HPP__
#define __KAMIKAZE_HPP__

// AOS Includes
#include "Enemy.hpp"

class Kamikaze : public Enemy
{
  public:
    Kamikaze(const std::string& p_Keyname);

    void Update(float p_DeltaTime);

  private:
    float m_IdleDelay;
    bool m_HasFoundTarget;
};

#endif
