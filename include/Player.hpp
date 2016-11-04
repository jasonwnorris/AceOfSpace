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

    const PlayerShip* GetPlayerShip() const;
    int GetLives() const;
    int GetScore() const;

    static void AddPlayers();
    static void RemovePlayers();

    static void SpawnPlayer(int p_Index);
    static void DestroyPlayer(PlayerShip* p_PlayerShip);

    static void ProcessInput(Uint32 p_EventType, SDL_Keycode p_Keycode);
    void ProcessInput(Uint32 p_EventType, SDL_Keycode p_Keycode, int p_Index);

    static void AwardPoints(int p_Amount);

  private:
    PlayerShip* m_PlayerShip;
    int m_Lives;
    int m_Score;
};

#endif
