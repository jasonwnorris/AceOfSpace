// Game.cpp //
#include "Game.h"

#include "Config.h"
#include "Sound.h"
#include "Level.h"
#include "Player.h"
#include "Boss.h"

Game::Game()
{
	printf("Initializing SDL... ");
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
	}
	printf("complete!\n");

    SDL_WM_SetCaption("Ace of Space", NULL);
    SDL_ShowCursor(SDL_DISABLE);
    
    printf("Initializing TTF... ");
    if(TTF_Init() < 0)
    {
        fprintf(stderr, "Unable to initialize TTF: %s\n", SDL_GetError());
        exit(1);
	}
	printf("complete!\n");

    printf("Initializing audio... ");
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        fprintf(stderr, "Unable to initialize audio: %s\n", SDL_GetError());
        exit(1);
	}
	printf("complete!\n");
    
    printf("Initializing screen... ");
	screen = SDL_SetVideoMode(ScreenWidth, ScreenHeight, ScreenBPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
	
	if(screen == NULL)
	{
		fprintf(stderr, "Failed to initialize the screen.\n");
		exit(1);
	}
	printf("complete!\n");
	
	done = false;
	frame = 0;
	gamestate = STATE_MENU;
	singlePlayer = true;
	showDebug = false;
}

Game::~Game()
{
	printf("Closing audio... ");
    Mix_CloseAudio();
	printf("complete!\n");
	
	printf("Closing TTF... ");
    TTF_Quit();
	printf("complete!\n");
	
	printf("Closing SDL... ");
	SDL_Quit();
	printf("complete!\n");
	
	printf("Game ended successfully!");
}

void Game::OnExecute()
{
	OnStart();
	
    while(!done)
    {
        OnThink();
		OnUpdate();
		OnRender();
    }
    
    OnEnd();
}

void Game::OnStart()
{
	Texture::LoadTextures();
	Sound::LoadSounds();
    Sound::PlaySound("Intro");
}

void Game::OnEnd()
{
	Texture::UnloadTextures();
	Sound::UnloadSounds();
	Player::RemovePlayers();
	Object::RemoveAll();
}

void Game::OnThink()
{
	while(SDL_PollEvent(&event))
    {
		if(gamestate == STATE_MENU)
		{
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_RETURN)
                {
                    gamestate = STATE_PLAYING;
					Level::LevelOne.BuildLevel();
					Player::AddPlayers();
					Player::SpawnPlayer(PLAYER_ONE);
					if(!singlePlayer)
						Player::SpawnPlayer(PLAYER_TWO);
                    Sound::PlaySound("Theme");
				}
				else if(event.key.keysym.sym == SDLK_1)
				    singlePlayer = !singlePlayer;
				else if(event.key.keysym.sym == SDLK_2)
				    gamestate = STATE_CONTROLS;
				else if(event.key.keysym.sym == SDLK_3)
				    gamestate = STATE_CREDITS;
			}
		}
		else if(gamestate == STATE_CONTROLS || gamestate == STATE_CREDITS)
		{
			if(event.type == SDL_KEYDOWN)
			    if(event.key.keysym.sym == SDLK_RETURN)
			        gamestate = STATE_MENU;
		}
		else if(gamestate == STATE_GAMEOVER || gamestate == STATE_VICTORY)
		{
			if(event.type == SDL_KEYDOWN)
			    if(event.key.keysym.sym == SDLK_RETURN)
			    {
			        gamestate = STATE_MENU;
					Player::RemovePlayers();
					Boss::RemoveBoss();
					Object::RemoveAll();
        			Sound::PlaySound("Intro");
				}
		}
		else if(gamestate == STATE_PLAYING)
		{
            Player::ProcessInput(event);
            
            if(event.type == SDL_KEYDOWN)
            {
				if(event.key.keysym.sym == SDLK_RSHIFT)
				    singlePlayer = false;
                if(event.key.keysym.sym == SDLK_RETURN)
                    gamestate = STATE_PAUSED;
			}
		}
		else if(gamestate == STATE_PAUSED)
		{
            if(event.type == SDL_KEYDOWN)
                if(event.key.keysym.sym == SDLK_RETURN)
                    gamestate = STATE_PLAYING;
		}

        if(event.type == SDL_KEYDOWN)
        {
			if(event.key.keysym.sym == SDLK_ESCAPE)
				done = true;
			if(event.key.keysym.sym == SDLK_TAB)
			    showDebug = !showDebug;
		}
				
		if(event.type == SDL_QUIT)
			done = true;
    }
}

void Game::OnUpdate()
{
	float deltaTime = timer.getDeltaTime();
	
	if(gamestate == STATE_PLAYING)
	{
		Object::UpdateObjects(deltaTime);
		Level::LevelOne.Update(deltaTime);
		starfield.Update(deltaTime);
		
		if(singlePlayer)
		{
			if(Player::Players[0].lives <= 0)
			{
			    gamestate = STATE_GAMEOVER;
	        	Sound::PlaySound("GameOver");
			}
		}
		else
		{
			if(Player::Players[0].lives + Player::Players[1].lives <= 0)
			{
			    gamestate = STATE_GAMEOVER;
	        	Sound::PlaySound("GameOver");
			}
		}
		
		if(Boss::FinalBoss.spawned && Boss::FinalBoss.killed)
		{
		    gamestate = STATE_VICTORY;
        	Sound::PlaySound("Victory");
		}
	}
	
	++frame;
}

void Game::OnRender()
{
    SDL_FillRect(screen, NULL, 0);
    
    if(gamestate == STATE_MENU)
	{
		DrawTitle();
	}
	else if(gamestate == STATE_CONTROLS)
	{
		DrawControls();
	}
	else if(gamestate == STATE_CREDITS)
	{
		DrawCredits();
	}
	else if(gamestate == STATE_PLAYING)
	{
		Object::RenderObjects(screen);
		DrawHUD();
	}
	else if(gamestate == STATE_PAUSED)
	{
		Object::RenderObjects(screen);
		DrawHUD();
		DrawPaused();
	}
	else if(gamestate == STATE_GAMEOVER)
	{
		Object::RenderObjects(screen);
		DrawHUD();
		DrawGameOver();
	}
	else if(gamestate == STATE_VICTORY)
	{
		Object::RenderObjects(screen);
		DrawHUD();
		DrawVictory();
	}
	
	if(showDebug)
		DrawDebug();
    
    SDL_Flip(screen);
}

// helper functions to draw various parts of the game

void Game::DrawHUD()
{
	// player 1 HUD
    SDL_Rect health1 = {20, ScreenHeight - 25, 200, 10};
    SDL_FillRect(screen, &health1, SDL_MapRGB(screen->format, 50, 50, 50));

    if(Player::Players[0].ship != NULL)
	{
		health1.w = Player::Players[0].ship->health * 2;
    	SDL_FillRect(screen, &health1, SDL_MapRGB(screen->format, 200, 50, 50));
	}

    for(int i = 0; i < Player::Players[0].lives; ++i)
    {
		SDL_Rect box = {(i + 1) * 20, ScreenHeight - 45, 10, 10};
		SDL_FillRect(screen, &box, SDL_MapRGB(screen->format, 255, 255, 255));
	}

	// player 2 HUD
	if(!singlePlayer)
	{
	    SDL_Rect health2 = {ScreenWidth - 220, ScreenHeight - 25, 200, 10};
	    SDL_FillRect(screen, &health2, SDL_MapRGB(screen->format, 50, 50, 50));

        if(Player::Players[1].ship != NULL)
    	{
			health2.x = ScreenWidth - 220 + (PlayerHealth - Player::Players[1].ship->health) * 2;
    		health2.w = Player::Players[1].ship->health * 2;
        	SDL_FillRect(screen, &health2, SDL_MapRGB(screen->format, 50, 50, 200));
		}

        for(int i = 0; i < Player::Players[1].lives; ++i)
        {
			SDL_Rect box = {ScreenWidth - 10 - (i + 1) * 20, ScreenHeight - 45, 10, 10};
			SDL_FillRect(screen, &box, SDL_MapRGB(screen->format, 255, 255, 255));
		}
	}

	// display score
	char buffer[20];
	sprintf(buffer, "%d", Player::Players[0].score);
	Texture::DrawText(screen, "SCORE", 10, ScreenWidth / 2, ScreenHeight - 35, 255, 255, 255);
	Texture::DrawText(screen, buffer,  14, ScreenWidth / 2, ScreenHeight - 20, 255, 255, 255);

	// boss HUD
	if(Boss::FinalBoss.spawned && !Boss::FinalBoss.killed)
	{
		int barWidth = ScreenWidth - 40;
		SDL_Rect boss = {20, 20, barWidth, 10};
    	SDL_FillRect(screen, &boss, SDL_MapRGB(screen->format, 50, 50, 50));

    	if(Boss::FinalBoss.boss != NULL)
    	{
			boss.w = (Sint16)(1.0f * Boss::FinalBoss.boss->health / BossHealth * barWidth);
    		SDL_FillRect(screen, &boss, SDL_MapRGB(screen->format, 50, 200, 50));
		}
	}
}

void Game::DrawTitle()
{
	SDL_Surface* titleSurf = Texture::TextureList["Title"]->textures[0];
	SDL_Rect titleRect = {ScreenWidth / 2 - titleSurf->w / 2, ScreenHeight / 2 - titleSurf->h / 2 - 100};
	SDL_BlitSurface(titleSurf, NULL, screen, &titleRect);

	Texture::DrawText(screen, "Press ENTER to Start", 25, ScreenWidth / 2, ScreenHeight / 2 + 75, 255, 255, 255);

	if(singlePlayer)
	    Texture::DrawText(screen, "1-Player", 20, ScreenWidth / 2, ScreenHeight / 2 + 100, 255, 255, 255);
	else
	    Texture::DrawText(screen, "2-Player", 20, ScreenWidth / 2, ScreenHeight / 2 + 100, 255, 255, 255);

	Texture::DrawText(screen, "Players",  20, ScreenWidth / 2 - 100, ScreenHeight / 2 + 150, 255, 255, 255);
	Texture::DrawText(screen, "(1)",      20, ScreenWidth / 2 + 100, ScreenHeight / 2 + 150, 255, 255, 255);
	Texture::DrawText(screen, "Controls", 20, ScreenWidth / 2 - 100, ScreenHeight / 2 + 175, 255, 255, 255);
	Texture::DrawText(screen, "(2)",      20, ScreenWidth / 2 + 100, ScreenHeight / 2 + 175, 255, 255, 255);
	Texture::DrawText(screen, "Credits",  20, ScreenWidth / 2 - 100, ScreenHeight / 2 + 200, 255, 255, 255);
	Texture::DrawText(screen, "(3)",      20, ScreenWidth / 2 + 100, ScreenHeight / 2 + 200, 255, 255, 255);
	Texture::DrawText(screen, "Debug",    20, ScreenWidth / 2 - 100, ScreenHeight / 2 + 225, 255, 255, 255);
	Texture::DrawText(screen, "(Tab)",    20, ScreenWidth / 2 + 100, ScreenHeight / 2 + 225, 255, 255, 255);
	Texture::DrawText(screen, "Exit",     20, ScreenWidth / 2 - 100, ScreenHeight / 2 + 250, 255, 255, 255);
	Texture::DrawText(screen, "(Esc)",    20, ScreenWidth / 2 + 100, ScreenHeight / 2 + 250, 255, 255, 255);
}

void Game::DrawControls()
{
	Texture::DrawText(screen, "CONTROLS", 35, ScreenWidth / 2,  40, 255, 255, 255);

	SDL_Surface* keySurf = Texture::TextureList["Keyboard"]->textures[0];
	SDL_Rect keyRect = {ScreenWidth / 2 - keySurf->w / 2, ScreenHeight / 2 - keySurf->h / 2};
	SDL_BlitSurface(keySurf, NULL, screen, &keyRect);

	Texture::DrawText(screen, "Press ENTER to Return to Main Menu", 16, ScreenWidth / 2, ScreenHeight - 40, 255, 255, 255);
}

void Game::DrawCredits()
{
	Texture::DrawText(screen, "CREDITS",      35, ScreenWidth / 2,  40, 255, 255, 255);
	Texture::DrawText(screen, "Programming",  15, ScreenWidth / 2, 150, 255, 255, 255);
	Texture::DrawText(screen, "Jason Norris", 25, ScreenWidth / 2, 170, 255, 255, 255);
	Texture::DrawText(screen, "Artwork",      15, ScreenWidth / 2, 250, 255, 255, 255);
	Texture::DrawText(screen, "Jason Norris", 25, ScreenWidth / 2, 270, 255, 255, 255);
	Texture::DrawText(screen, "Music",        15, ScreenWidth / 2, 350, 255, 255, 255);
	Texture::DrawText(screen, "Andy Cubrich", 25, ScreenWidth / 2, 370, 255, 255, 255);
	Texture::DrawText(screen, "Press ENTER to Return to Main Menu", 16, ScreenWidth / 2, ScreenHeight - 40, 255, 255, 255);
}

void Game::DrawPaused()
{
	SDL_Rect rect = {0, 0, ScreenWidth, ScreenHeight};
	Texture::FillAlphaRect(screen, rect, 0, 0, 0, 128);
	Texture::DrawText(screen, "PAUSED", 30, ScreenWidth / 2, ScreenHeight / 2, 255, 255, 255);
}

void Game::DrawGameOver()
{
	SDL_Rect rect = {0, 0, ScreenWidth, ScreenHeight};
	Texture::FillAlphaRect(screen, rect, 255, 0, 0, 128);
	Texture::DrawText(screen, "FAILURE", 95, ScreenWidth / 2, ScreenHeight / 2, 255, 0, 0);
	Texture::DrawText(screen, "Press ENTER to Return to Main Menu", 16, ScreenWidth / 2, ScreenHeight / 2 + 50, 255, 0, 0);
}

void Game::DrawVictory()
{
	SDL_Rect rect = {0, 0, ScreenWidth, ScreenHeight};
	Texture::FillAlphaRect(screen, rect, 0, 255, 0, 128);
	Texture::DrawText(screen, "SUCCESS", 95, ScreenWidth / 2, ScreenHeight / 2, 0, 255, 0);
	Texture::DrawText(screen, "Press ENTER to Return to Main Menu", 16, ScreenWidth / 2, ScreenHeight / 2 + 50, 0, 255, 0);
}

void Game::DrawDebug()
{
	char buffer[15];
	sprintf(buffer, "FPS: %d", (int)(frame / timer.getStartTime()));
	Texture::DrawText(screen, buffer, 14, 10, 10, 255, 255, 255, false);
	sprintf(buffer, "Objects: %d", Object::ObjectList.size());
	Texture::DrawText(screen, buffer, 14, 10, 30, 255, 255, 255, false);
}
