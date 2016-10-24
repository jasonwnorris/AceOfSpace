// Item.hpp

#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include "GameObject.hpp"

class Item : public GameObject
{
  public:
    Item(string keyname);

    void Collide(GameObject* object);

    virtual void InflictBonus(GameObject* object) { }
};

#endif
