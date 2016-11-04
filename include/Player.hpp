// Player.hpp

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

// AOS Includes
#include "PlayerShip.hpp"

class Player
{
  public:
    Player();

    static Player* Players;

    static void AddPlayers();
    static void RemovePlayers();

    static void SpawnPlayer(int p_Index);
    static void DestroyPlayer(PlayerShip* p_PlayerShip);

    static void ProcessInput(SDL_Event& p_Event);
    void ProcessInput(SDL_Event& p_Event, int p_Index);

    static void AwardPoints(int p_Amount);

    PlayerShip* m_PlayerShip;
    int m_Lives;
    int m_Score;
};

#endif
