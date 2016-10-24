// Kamikaze.cpp //
#include "Kamikaze.hpp"

#include "Player.hpp"

Kamikaze::Kamikaze(string keyname) : Enemy(keyname)
{
  pointValue = KamikazePointValue;
  health = KamikazeHealth;
  speed = KamikazeIdleSpeed;
  idleDelay = KamikazeIdleDelay;
  foundTarget = false;
}

void Kamikaze::Update(float deltaTime)
{
  if (!foundTarget)
  {
    idleDelay -= deltaTime;

    if (idleDelay < 0)
    {
      GameObject* target = PickRandomObject(&PlayerShip::PlayerShipList);
      direction = target->position - position;

      speed = KamikazeAttackSpeed;
      foundTarget = true;
    }
  }

  Enemy::Update(deltaTime);
}
