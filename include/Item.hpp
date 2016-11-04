// Item.hpp

#ifndef __ITEM_HPP__
#define __ITEM_HPP__

// AOS Includes
#include "GameObject.hpp"

class Item : public GameObject
{
  public:
    Item(const std::string& p_Keyname);

    void Collide(GameObject* p_Object);

    virtual void InflictBonus(GameObject* p_Object) { }
};

#endif
