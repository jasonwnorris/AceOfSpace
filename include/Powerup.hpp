// Powerup.hpp

#ifndef __POWERUP_HPP__
#define __POWERUP_HPP__

// AOS Includes
#include "Item.hpp"

class Powerup : public Item
{
  public:
    Powerup(const std::string& p_Keyname);

    void InflictBonus(GameObject* p_GameObject);

  private:
    std::string m_Type;
};

#endif
