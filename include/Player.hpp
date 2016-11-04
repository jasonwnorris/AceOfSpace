// Player.hpp

#ifndef __PLAYERSHIP_HPP__
#define __PLAYERSHIP_HPP__

// AOS Includes
#include "GameObject.hpp"

enum PlayerIndex
{
  PLAYER_ONE,
  PLAYER_TWO,
};

class PlayerShip : public GameObject
{
  public:
    PlayerShip(const std::string& p_Keyname);

    static std::vector<GameObject*> PlayerShipList;

    void Update(float p_DeltaTime);

    static void RemoveKilled();
    static void RemoveAll();
    void Remove();

    void Collide(GameObject* p_Object);

    bool m_IsMovingUp;
    bool m_IsMovingDown;
    bool m_IsMovingLeft;
    bool m_IsMovingRight;
    bool m_IsShooting;

  private:
    void FireBullet();

    float m_LastFired;
};

class Player
{
  public:
    Player();

    static Player* Players;

    static void AddPlayers();
    static void RemovePlayers();

    static void SpawnPlayer(int index);
    static void DestroyPlayer(PlayerShip* ship);

    static void ProcessInput(SDL_Event& event);
    void ProcessInput(SDL_Event& event, int index);

    static void AwardPoints(int amount);

    PlayerShip* m_Ship;
    int m_Lives;
    int m_Score;
};

#endif
