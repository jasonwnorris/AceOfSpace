// Powerup.hpp

#ifndef __POWERUP_HPP__
#define __POWERUP_HPP__

// AOS Includes
#include "Item.hpp"

class Powerup : public Item
{
  public:
    Powerup(const std::string& keyname);

    void InflictBonus(GameObject* object);

  private:
    std::string type;
};

#endif
