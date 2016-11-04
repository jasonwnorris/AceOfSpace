// PlayerShip.hpp

#ifndef __PLAYERSHIP_HPP__
#define __PLAYERSHIP_HPP__

// AOS Includes
#include "GameObject.hpp"

class PlayerShip : public GameObject
{
  public:
    PlayerShip(const std::string& p_Keyname);

    static std::vector<GameObject*> PlayerShipList;

    void Update(float p_DeltaTime);

    static void RemoveKilled();
    static void RemoveAll();
    void Remove();

    void Collide(GameObject* p_GameObject);

    bool m_IsMovingUp;
    bool m_IsMovingDown;
    bool m_IsMovingLeft;
    bool m_IsMovingRight;
    bool m_IsShooting;

  private:
    void FireBullet();

    float m_LastFired;
};

#endif
