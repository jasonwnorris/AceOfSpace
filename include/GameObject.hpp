// GameObject.hpp

#ifndef __GAMEOBJECT_HPP__
#define __GAMEOBJECT_HPP__

// AOS Includes
#include "Object.hpp"

class GameObject : public Object
{
  public:
    GameObject(const std::string& p_Keyname);
    virtual ~GameObject();

    int GetHealth() const;

    void SetHealth(int p_Health);
    void SetWeaponType(int p_WeaponType);
    void SetCollisionList(std::vector<GameObject*>* p_CollisionList);

    virtual void Update(float p_DeltaTime);

    virtual void Collide(GameObject* p_GameObject);
    virtual void TakeDamage(int p_Amount);
    virtual void Explode();

    virtual void RemoveOffScreen();

    GameObject* PickRandomObject(std::vector<GameObject*>* p_PickList);

  protected:
    int m_Health;
    float m_FlickerInterval;
    std::string m_ExplosionKeyname;
    int m_WeaponType;
    std::vector<GameObject*>* m_CollisionList;
};

#endif
