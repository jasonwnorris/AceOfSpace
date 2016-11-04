// Player.cpp

// STL Includes
#include <sstream>
// AOS Includes
#include "Player.hpp"
#include "Bullet.hpp"
#include "Missile.hpp"
#include "Fireball.hpp"

#define PLAYER_COUNT 2

static const SDL_Keycode c_StartKey[PLAYER_COUNT] = { SDLK_SPACE, SDLK_RSHIFT };
static const SDL_Keycode c_UpKey[PLAYER_COUNT] = { SDLK_w, SDLK_UP };
static const SDL_Keycode c_DownKey[PLAYER_COUNT] = { SDLK_s, SDLK_DOWN };
static const SDL_Keycode c_LeftKey[PLAYER_COUNT] = { SDLK_a, SDLK_LEFT };
static const SDL_Keycode c_RightKey[PLAYER_COUNT] = { SDLK_d, SDLK_RIGHT };
static const SDL_Keycode c_FireKey[PLAYER_COUNT] = { SDLK_j, SDLK_RCTRL };

Player* Player::Players = nullptr;

Player::Player()
{
  m_PlayerShip = nullptr;
  m_Lives = c_PlayerLives;
  m_Score = 0;
}

const PlayerShip* Player::GetPlayerShip() const
{
  return m_PlayerShip;
}

int Player::GetLives() const
{
  return m_Lives;
}

int Player::GetScore() const
{
  return m_Score;
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

void Player::ProcessInput(Uint32 p_EventType, SDL_Keycode p_Keycode)
{
  for (int i = 0; i < PLAYER_COUNT; ++i)
  {
    Players[i].ProcessInput(p_EventType, p_Keycode, i);
  }
}

void Player::ProcessInput(Uint32 p_EventType, SDL_Keycode p_Keycode, int p_Index)
{
  switch (p_EventType)
  {
    case SDL_KEYDOWN:
      if (m_PlayerShip != nullptr)
      {
        if (p_Keycode == c_UpKey[p_Index])
        {
          m_PlayerShip->SetMovingUp(true);
        }
        if (p_Keycode == c_DownKey[p_Index])
        {
          m_PlayerShip->SetMovingDown(true);
        }
        if (p_Keycode == c_LeftKey[p_Index])
        {
          m_PlayerShip->SetMovingLeft(true);
        }
        if (p_Keycode == c_RightKey[p_Index])
        {
          m_PlayerShip->SetMovingRight(true);
        }
        if (p_Keycode == c_FireKey[p_Index])
        {
          m_PlayerShip->SetShooting(true);
        }
      }
      else
      {
        if (p_Keycode == c_StartKey[p_Index])
        {
          SpawnPlayer(p_Index);
        }
      }
      break;
    case SDL_KEYUP:
      if (m_PlayerShip != nullptr)
      {
        if (p_Keycode == c_UpKey[p_Index])
        {
          m_PlayerShip->SetMovingUp(false);
        }
        if (p_Keycode == c_DownKey[p_Index])
        {
          m_PlayerShip->SetMovingDown(false);
        }
        if (p_Keycode == c_LeftKey[p_Index])
        {
          m_PlayerShip->SetMovingLeft(false);
        }
        if (p_Keycode == c_RightKey[p_Index])
        {
          m_PlayerShip->SetMovingRight(false);
        }
        if (p_Keycode == c_FireKey[p_Index])
        {
          m_PlayerShip->SetShooting(false);
        }
      }
      break;
  }
}

void Player::AwardPoints(int p_Amount)
{
  for (int i = 0; i < PLAYER_COUNT; ++i)
  {
    Players[i].m_Score += p_Amount;
  }
}
