// GameObject.hpp

#ifndef __GAMEOBJECT_HPP__
#define __GAMEOBJECT_HPP__

// AOS Includes
#include "Object.hpp"

class GameObject : public Object
{
  public:
    GameObject(const std::string& keyname);
    virtual ~GameObject();

    virtual void Update(float deltaTime);

    virtual void Collide(GameObject* object) { }
    virtual void TakeDamage(int amount);
    virtual void Explode();

    virtual void RemoveOffScreen();

    GameObject* PickRandomObject(std::vector<GameObject*>* PickList);

    int m_Health;
    float m_FlickerInterval;
    std::string m_ExplosionKeyname;
    int m_WeaponType;

    std::vector<GameObject*>* CollisionList;
};

#endif
