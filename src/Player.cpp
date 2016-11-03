// Player.cpp

// AOS Includes
#include "Player.hpp"
#include "Sound.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Missile.hpp"
#include "Fireball.hpp"

#define PLAYER_COUNT 2

SDL_Keycode StartKey[2] = {SDLK_SPACE, SDLK_RSHIFT};
SDL_Keycode UpKey[2]    = {SDLK_w,     SDLK_UP};
SDL_Keycode DownKey[2]  = {SDLK_s,     SDLK_DOWN};
SDL_Keycode LeftKey[2]  = {SDLK_a,     SDLK_LEFT};
SDL_Keycode RightKey[2] = {SDLK_d,     SDLK_RIGHT};
SDL_Keycode FireKey[2]  = {SDLK_j,     SDLK_RCTRL};

Player* Player::Players = nullptr;

Player::Player()
{
  ship = nullptr;
  lives = PlayerLives;
  score = 0;
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
  delete [] Players;
  Players = nullptr;
}

void Player::SpawnPlayer(int index)
{
  if (Players[index].ship == nullptr && Players[index].lives > 0)
  {
    char player[8];
    snprintf(player, 8, "Player%d", index + 1);
    Players[index].ship = new PlayerShip(player);
  }
}

void Player::DestroyPlayer(PlayerShip* ship)
{
  for (int i = 0; i < PLAYER_COUNT; ++i)
  {
    if (Players[i].ship == ship)
    {
      Players[i].ship = nullptr;
      Players[i].lives--;
    }
  }
}

void Player::ProcessInput(SDL_Event& event)
{
  for (int i = 0; i < PLAYER_COUNT; ++i)
  {
    Players[i].ProcessInput(event, i);
  }
}

void Player::ProcessInput(SDL_Event& event, int index)
{
  if (ship == nullptr)
  {
    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == StartKey[index])
      {
        SpawnPlayer(index);
      }
    }
  }
  else
  {
    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == UpKey[index])
      {
        ship->movingUp = true;
      }
      if (event.key.keysym.sym == DownKey[index])
      {
        ship->movingDown = true;
      }
      if (event.key.keysym.sym == LeftKey[index])
      {
        ship->movingLeft = true;
      }
      if (event.key.keysym.sym == RightKey[index])
      {
        ship->movingRight = true;
      }
      if (event.key.keysym.sym == FireKey[index])
      {
        ship->shooting = true;
      }
    }
    else if (event.type == SDL_KEYUP)
    {
      if (event.key.keysym.sym == UpKey[index])
      {
        ship->movingUp = false;
      }
      if (event.key.keysym.sym == DownKey[index])
      {
        ship->movingDown = false;
      }
      if (event.key.keysym.sym == LeftKey[index])
      {
        ship->movingLeft = false;
      }
      if (event.key.keysym.sym == RightKey[index])
      {
        ship->movingRight = false;
      }
      if (event.key.keysym.sym == FireKey[index])
      {
        ship->shooting = false;
      }
    }
  }
}

void Player::AwardPoints(int amount)
{
  for (int i = 0; i < PLAYER_COUNT; ++i)
  {
    Players[i].score += amount;
  }
}

// PlayerShip.cpp //

std::vector<GameObject*> PlayerShip::PlayerShipList;

PlayerShip::PlayerShip(const std::string& keyname) : GameObject(keyname)
{
  position = Vector2f(ScreenWidth / 2.0f, static_cast<float>(ScreenHeight - sprite->texture->tileHeight - PlayerSpawnOffset));
  speed = PlayerSpeed;
  health = PlayerHealth;
  explosionKeyname = "Explosion";
  weaponType = WEAPON_BULLET;
  CollisionList = &Enemy::EnemyList;

  movingUp = false;
  movingDown = false;
  movingLeft = false;
  movingRight = false;
  shooting = false;

  lastFired = 0.0f;

  PlayerShipList.push_back(this);
}

void PlayerShip::Update(float deltaTime)
{
  direction = Vector2f::Zero;

  if (movingUp)
  {
    direction.Y -= 1;
  }
  if (movingDown)
  {
    direction.Y += 1;
  }
  if (movingLeft)
  {
    direction.X -= 1;
  }
  if (movingRight)
  {
    direction.X += 1;
  }

  lastFired += deltaTime;
  FireBullet();

  GameObject::Update(deltaTime);

  if (position.X < sprite->origin.X)
  {
    position.X = sprite->origin.X;
  }
  else if (position.X > ScreenWidth - sprite->origin.X)
  {
    position.X = ScreenWidth - sprite->origin.X;
  }

  if (position.Y < sprite->origin.Y)
  {
    position.Y = sprite->origin.Y;
  }
  else if (position.Y > ScreenHeight - sprite->origin.Y)
  {
    position.Y = ScreenHeight - sprite->origin.Y;
  }
}

void PlayerShip::RemoveKilled()
{
  for (std::vector<GameObject*>::iterator Iter = PlayerShipList.begin(); Iter != PlayerShipList.end(); Iter += 0)
  {
    if ((*Iter)->dead)
    {
      Iter = PlayerShipList.erase(Iter);
    }
    else
    {
      ++Iter;
    }
  }
}

void PlayerShip::RemoveAll()
{
  for (std::vector<GameObject*>::iterator Iter = PlayerShipList.begin(); Iter != PlayerShipList.end(); Iter += 0)
  {
    Iter = PlayerShipList.erase(Iter);
  }
}

void PlayerShip::Remove()
{
  Player::DestroyPlayer(this);

  GameObject::Remove();
}

void PlayerShip::Collide(GameObject* object)
{
  int objectHealth = object->health;
  object->TakeDamage(this->health);
  this->TakeDamage(objectHealth);
}

void PlayerShip::FireBullet()
{
  if (shooting)
  {
    if (weaponType == WEAPON_BULLET)
    {
      if (lastFired > PlayerFireDelay)
      {
        int total = 3;
        for (int i = 0; i < total; ++i)
        {
          Projectile* projectile = new Bullet("Bullet");
          projectile->position = position + Vector2f::Left * (1 - i) * 5.0f + Vector2f::Up * 20.0f;
          projectile->direction = Vector2f::Up;
          projectile->CollisionList = &Enemy::EnemyList;
        }

        lastFired = 0.0f;
      }
    }
    else if (weaponType == WEAPON_MISSILE || weaponType == WEAPON_PLASMA)
    {
      if (lastFired > PlayerFireDelay)
      {
        int total = 5;
        for (int i = 0; i < total; ++i)
        {
          Projectile* projectile = nullptr;

          if (weaponType == WEAPON_MISSILE)
          {
            projectile = new Missile("Missile");
          }
          else if (weaponType == WEAPON_PLASMA)
          {
            projectile = new Bullet("Plasma");
          }

          projectile->position = position + Vector2f::Up * 20.0f;
          projectile->direction = Vector2f::Right * (i - (total / 2)) / 10.0f + Vector2f::Up;
          projectile->CollisionList = &Enemy::EnemyList;
        }

        lastFired = 0.0f;
      }
    }
    else if (weaponType == WEAPON_FIREBALL)
    {
      if (lastFired > FireballFireDelay)
      {
        Projectile* projectile = new Fireball("Flames");
        projectile->position = position + Vector2f::Up * 28.0f;
        projectile->direction = Vector2f::Right * (rand() % 101 - 50) / 100.0f + Vector2f::Up;
        projectile->CollisionList = &Enemy::EnemyList;

        lastFired = 0.0f;
      }
    }
  }
}
