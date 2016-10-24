// Powerup.hpp

#ifndef __POWERUP_HPP__
#define __POWERUP_HPP__

#include "Item.hpp"

class Powerup : public Item
{
  public:
    Powerup(string keyname);

    void InflictBonus(GameObject* object);

  private:
    string type;
};

#endif
