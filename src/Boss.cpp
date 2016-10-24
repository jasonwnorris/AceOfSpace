// Boss.cpp //
#include "Boss.hpp"

#include "Sound.hpp"

Boss Boss::FinalBoss;

Boss::Boss()
{
  boss = NULL;
  spawned = false;
  killed = false;
}

void Boss::RemoveBoss()
{
  FinalBoss.boss = NULL;
  FinalBoss.spawned = false;
  FinalBoss.killed = false;
}

void Boss::SpawnBoss()
{
  FinalBoss.boss = new BossEnemy("Boss");
  FinalBoss.spawned = true;
  Sound::PlaySound("Boss");
}

void Boss::DestroyBoss()
{
  FinalBoss.boss = NULL;
  FinalBoss.killed = true;
}

// BossEnemy.cpp //

#include "Bullet.hpp"
#include "Player.hpp"

BossEnemy::BossEnemy(std::string keyname) : Enemy(keyname)
{
  pointValue = BossPointValue;

  position = Vector(ScreenWidth / 2, -sprite->origin.Y);
  direction = Vector(0, 1);
  speed = BossSpeed;
  health = BossHealth;

  childrenAngle = 0.0f;
  fireAngle = 0.0f;
  lastFired = 0.0f;

  leftHand = new Miniboss("LeftHand");
  rightHand = new Miniboss("RightHand");
}

// basic movement behavior, comes part way down screen then patrols left-right
void BossEnemy::Update(float deltaTime)
{
  Enemy::Update(deltaTime);

  UpdateChildren();

  if (direction.X < 0)
  {
    if (position.X < 300)
      direction = Vector(1, 0);
  }
  else if (direction.X > 0)
  {
    if (position.X > ScreenWidth - 300)
      direction = Vector(-1, 0);
  }
  else
  {
    if (position.Y > ScreenHeight / 3)
      if (rand() % 2 == 0)
        direction = Vector(1, 0);
    else
      direction = Vector(-1, 0);
  }

  childrenAngle += BossChildrenRotation;

  // increase challenge when half dead (or half alive?)
  if (health > BossHealth / 2)
  {
    fireAngle += BossFireRotation;
    lastFired += deltaTime;
  }
  else
  {
    fireAngle += BossFireRotation * 2;
    lastFired += deltaTime * 2;
  }

  if (lastFired > BossFireDelay)
    FireBullet();
}

// helper function to update objects that this parent controls
void BossEnemy::UpdateChildren()
{
  if (leftHand != NULL)
    if (leftHand->health > 0)
      leftHand->position = position + Vector(-200, 75) + Vector::CalculateDirection(-childrenAngle) * 25;
    else
      leftHand = NULL;

  if (rightHand != NULL)
    if (rightHand->health > 0)
      rightHand->position = position + Vector(200, 75) + Vector::CalculateDirection(childrenAngle) * -25;
    else
      rightHand = NULL;
}

void BossEnemy::RemoveOffScreen()
{
  SDL_Rect bounds = {-ScreenWidth, -ScreenHeight, ScreenWidth * 3, ScreenHeight * 3};
  SDL_Rect intersect = Intersection(GetBounds(), bounds);

  if (intersect.w == 0 && intersect.h == 0)
    Remove();
}

void BossEnemy::Remove()
{
  Boss::DestroyBoss();

  Enemy::Remove();
}

// fire bullets in a rotating spiral
// it looks neat!
void BossEnemy::FireBullet()
{
  Bullet* bullet = new Bullet("NeonOrb");
  bullet->position = position;
  bullet->direction = Vector::CalculateDirection(fireAngle);
  bullet->speed = 100.0f;
  bullet->CollisionList = &PlayerShip::PlayerShipList;

  lastFired = 0.0f;
}
