// Player.h //
#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "GameObject.h"

enum PlayerIndex
{
	PLAYER_ONE,
	PLAYER_TWO,
};

class PlayerShip : public GameObject
{
	public:
		PlayerShip(string keyname);
		
		static vector<GameObject*> PlayerShipList;

		void Update(float deltaTime);

		static void RemoveKilled();
		static void RemoveAll();
		void Remove();

		void Collide(GameObject* object);

		bool movingUp;
		bool movingDown;
		bool movingLeft;
		bool movingRight;
		bool shooting;

	private:
		void FireBullet();
		
		float lastFired;
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

        PlayerShip* ship;
        int lives;
        int score;
};

#endif
