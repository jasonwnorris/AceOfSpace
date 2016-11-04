// Missile.hpp

#ifndef __MISSILE_HPP__
#define __MISSILE_HPP__

// AOS Includes
#include "Projectile.hpp"

class Missile : public Projectile
{
  public:
    Missile(const std::string& p_Keyname);

    void Update(float p_DeltaTime);

    void RemoveOffScreen();

  private:
    GameObject* m_Target;
};

#endif
