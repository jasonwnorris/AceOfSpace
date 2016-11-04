// Player.cpp

// STL Includes
#include <sstream>
// AOS Includes
#include "Player.hpp"
#include "Bullet.hpp"
#include "Missile.hpp"
#include "Fireball.hpp"

#define PLAYER_COUNT 2

SDL_Keycode StartKey[PLAYER_COUNT] = { SDLK_SPACE, SDLK_RSHIFT };
SDL_Keycode UpKey[PLAYER_COUNT] = { SDLK_w, SDLK_UP };
SDL_Keycode DownKey[PLAYER_COUNT] = { SDLK_s, SDLK_DOWN };
SDL_Keycode LeftKey[PLAYER_COUNT] = { SDLK_a, SDLK_LEFT };
SDL_Keycode RightKey[PLAYER_COUNT] = { SDLK_d, SDLK_RIGHT };
SDL_Keycode FireKey[PLAYER_COUNT] = { SDLK_j, SDLK_RCTRL };

Player* Player::Players = nullptr;

Player::Player()
{
  m_PlayerShip = nullptr;
  m_Lives = c_PlayerLives;
  m_Score = 0;
}

void Player::AddPlayers()
{
  Players = new Player[PLAYER_COUNT];

  for (int i = 0; i < PLAYER_COUNT; ++i)
  {
    Players[i] = Player();
  }
}

void Player::RemovePlayers()
{
  delete[] Players;
  Players = nullptr;
}

void Player::SpawnPlayer(int p_Index)
{
  if (Players[p_Index].m_PlayerShip == nullptr && Players[p_Index].m_Lives > 0)
  {
    std::stringstream ss;
    ss << "Player" << (p_Index + 1);
    Players[p_Index].m_PlayerShip = new PlayerShip(ss.str());
  }
}

void Player::DestroyPlayer(PlayerShip* p_PlayerShip)
{
  for (int i = 0; i < PLAYER_COUNT; ++i)
  {
    if (Players[i].m_PlayerShip == p_PlayerShip)
    {
      Players[i].m_PlayerShip = nullptr;
      --Players[i].m_Lives;
    }
  }
}

void Player::ProcessInput(SDL_Event& p_Event)
{
  for (int i = 0; i < PLAYER_COUNT; ++i)
  {
    Players[i].ProcessInput(p_Event, i);
  }
}

void Player::ProcessInput(SDL_Event& p_Event, int p_Index)
{
  if (m_PlayerShip == nullptr)
  {
    if (p_Event.type == SDL_KEYDOWN)
    {
      if (p_Event.key.keysym.sym == StartKey[p_Index])
      {
        SpawnPlayer(p_Index);
      }
    }
  }
  else
  {
    if (p_Event.type == SDL_KEYDOWN)
    {
      if (p_Event.key.keysym.sym == UpKey[p_Index])
      {
        m_PlayerShip->m_IsMovingUp = true;
      }
      if (p_Event.key.keysym.sym == DownKey[p_Index])
      {
        m_PlayerShip->m_IsMovingDown = true;
      }
      if (p_Event.key.keysym.sym == LeftKey[p_Index])
      {
        m_PlayerShip->m_IsMovingLeft = true;
      }
      if (p_Event.key.keysym.sym == RightKey[p_Index])
      {
        m_PlayerShip->m_IsMovingRight = true;
      }
      if (p_Event.key.keysym.sym == FireKey[p_Index])
      {
        m_PlayerShip->m_IsShooting = true;
      }
    }
    else if (p_Event.type == SDL_KEYUP)
    {
      if (p_Event.key.keysym.sym == UpKey[p_Index])
      {
        m_PlayerShip->m_IsMovingUp = false;
      }
      if (p_Event.key.keysym.sym == DownKey[p_Index])
      {
        m_PlayerShip->m_IsMovingDown = false;
      }
      if (p_Event.key.keysym.sym == LeftKey[p_Index])
      {
        m_PlayerShip->m_IsMovingLeft = false;
      }
      if (p_Event.key.keysym.sym == RightKey[p_Index])
      {
        m_PlayerShip->m_IsMovingRight = false;
      }
      if (p_Event.key.keysym.sym == FireKey[p_Index])
      {
        m_PlayerShip->m_IsShooting = false;
      }
    }
  }
}

void Player::AwardPoints(int p_Amount)
{
  for (int i = 0; i < PLAYER_COUNT; ++i)
  {
    Players[i].m_Score += p_Amount;
  }
}
