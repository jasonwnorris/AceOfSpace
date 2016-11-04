// Config.hpp

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

// STL Includes
#include <string>

static const int c_ScreenWidth = 800;
static const int c_ScreenHeight = 600;

static const std::string c_ResourcesPath = "resources/";
static const std::string c_FontFilename = c_ResourcesPath + "framd.ttf";
static const std::string c_LevelFilename = c_ResourcesPath + "level.txt";
static const std::string c_TexturesFilename = c_ResourcesPath + "textures.txt";
static const std::string c_SoundsFilename = c_ResourcesPath + "sounds.txt";

static const float c_DamageEffectTime = 0.09f;

static const float c_StarfieldSpawnTime = 0.05f;

static const int c_PlayerHealth = 100;
static const float c_PlayerSpeed = 300.0f;
static const int c_PlayerSpawnOffset = 20;
static const float c_PlayerFireDelay = 0.2f;
static const int c_PlayerLives = 5;

static const int c_BossPointValue = 5000;
static const int c_BossHealth = 7500;
static const float c_BossSpeed = 50.0f;
static const float c_BossFireDelay = 0.05f;
static const float c_BossFireRotation = 0.05f;
static const float c_BossChildrenRotation = 0.01f;

static const int c_MinibossPointValue = 1000;
static const int c_MinibossHealth = 2000;
static const float c_MinibossFireDelay = 1.0f;

static const int c_AsteroidPointValue = 10;
static const int c_AsteroidHealth = 50;
static const float c_AsteroidSpeed = 100.0f;

static const int c_StraightShooterPointValue = 20;
static const int c_StraightShooterHealth = 100;
static const float c_StraightShooterSpeed = 100.0f;
static const float c_StraightShooterFireDelay = 1.0f;

static const int c_TargetShooterPointValue = 25;
static const int c_TargetShooterHealth = 100;
static const float c_TargetShooterSpeed = 100.0f;
static const float c_TargetShooterFireDelay = 1.0f;

static const int c_KamikazePointValue = 15;
static const int c_KamikazeHealth = 75;
static const float c_KamikazeIdleDelay = 1.5f;
static const float c_KamikazeIdleSpeed = 100.0f;
static const float c_KamikazeAttackSpeed = 500.0f;

static const int c_BulletHealth = 8;
static const float c_BulletSpeed = 600.0f;

static const int c_MissileHealth = 5;
static const float c_MissileSpeed = 500.0f;
static const float c_MissileHomingStrength = 0.019f;

static const int c_FireballHealth = 2;
static const float c_FireballSpeed = 200.0f;
static const float c_FireballFadeoutTime = 0.8f;
static const float c_FireballFireDelay = 0.004f;

static const float c_ItemSpeed = 100.0f;

#endif
