// Config.hpp

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#define Maximum(a, b)  ((a > b) ? a : b)
#define Minimum(a, b)  ((a < b) ? a : b)

const int ScreenWidth = 800;
const int ScreenHeight = 600;
const int ScreenBPP = 32;

const float DamageEffectTime = 0.09f;

const float StarfieldSpawnTime = 0.05f;

const int PlayerHealth = 100;
const float PlayerSpeed = 300.0f;
const int PlayerSpawnOffset = 20;
const float PlayerFireDelay = 0.2f;
const int PlayerLives = 5;

const int BossPointValue = 5000;
const int BossHealth = 7500;
const float BossSpeed = 50.0f;
const float BossFireDelay = 0.05f;
const float BossFireRotation = 0.05f;
const float BossChildrenRotation = 0.01f;

const int MinibossPointValue = 1000;
const int MinibossHealth = 2000;
const float MinibossFireDelay = 1.0f;

const int AsteroidPointValue = 10;
const int AsteroidHealth = 50;
const float AsteroidSpeed = 100.0f;

const int StraightShooterPointValue = 20;
const int StraightShooterHealth = 100;
const float StraightShooterSpeed = 100.0f;
const float StraightShooterFireDelay = 1.0f;

const int TargetShooterPointValue = 25;
const int TargetShooterHealth = 100;
const float TargetShooterSpeed = 100.0f;
const float TargetShooterFireDelay = 1.0f;

const int KamikazePointValue = 15;
const int KamikazeHealth = 75;
const float KamikazeIdleDelay = 1.5f;
const float KamikazeIdleSpeed = 100.0f;
const float KamikazeAttackSpeed = 500.0f;

const int BulletHealth = 8;
const float BulletSpeed = 600.0f;

const int MissileHealth = 5;
const float MissileSpeed = 500.0f;
const float MissileHomingStrength = 0.019f;

const int FireballHealth = 2;
const float FireballSpeed = 200.0f;
const float FireballFadeoutTime = 0.8f;
const float FireballFireDelay = 0.004f;

const float ItemSpeed = 100.0f;

#endif
