// Missile.h //
#ifndef MISSILE_H
#define MISSILE_H

#include "Projectile.h"

class Missile : public Projectile
{
  public:
    Missile(string keyname);
    
    void Update(float deltaTime);
    
    void RemoveOffScreen();
    
  private:
    GameObject* target;
};

#endif
