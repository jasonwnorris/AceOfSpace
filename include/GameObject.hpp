// GameObject.hpp

#ifndef __GAMEOBJECT_HPP__
#define __GAMEOBJECT_HPP__

#include "Object.hpp"

class GameObject : public Object
{
  public:
    GameObject(std::string keyname);
    virtual ~GameObject();

    virtual void Update(float deltaTime);

    virtual void Collide(GameObject* object) { }
    virtual void TakeDamage(int amount);
    virtual void Explode();

    virtual void RemoveOffScreen();

    GameObject* PickRandomObject(std::vector<GameObject*>* PickList);

    int health;
    float flickerInterval;
    std::string explosionKeyname;
    int weaponType;

    std::vector<GameObject*>* CollisionList;
};

#endif
