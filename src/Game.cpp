// Game.cpp //
#include "Game.hpp"

#include "Config.hpp"
#include "Sound.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "Boss.hpp"

Game::Game()
{
  printf("Initializing SDL... ");
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
  printf("complete!\n");

  SDL_ShowCursor(SDL_DISABLE);

  printf("Initializing TTF... ");
  if (TTF_Init() < 0)
  {
    fprintf(stderr, "Unable to initialize TTF: %s\n", SDL_GetError());
    exit(1);
  }
  printf("complete!\n");

  printf("Initializing audio... ");
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
  {
    fprintf(stderr, "Unable to initialize audio: %s\n", SDL_GetError());
    exit(1);
  }
  printf("complete!\n");

  printf("Initializing window... ");
  window = SDL_CreateWindow("Ace of Space", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, 0);

  if (window == NULL)
  {
    fprintf(stderr, "Failed to initialize the window.\n");
    exit(1);
  }
  printf("complete!\n");

  printf("Initializing renderer... ");
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == NULL)
  {
    fprintf(stderr, "Failed to initialize the renderer.\n");
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
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  printf("complete!\n");

  printf("Game ended successfully!");
}

void Game::OnExecute()
{
  OnStart();

  while (!done)
  {
    OnThink();
    OnUpdate();
    OnRender();
  }

  OnEnd();
}

void Game::OnStart()
{
  Texture::LoadTextures(renderer);
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
  while (SDL_PollEvent(&event))
  {
    if (gamestate == STATE_MENU)
    {
      if (event.type == SDL_KEYDOWN)
      {
        if (event.key.keysym.sym == SDLK_RETURN)
        {
          gamestate = STATE_PLAYING;
          Level::LevelOne.BuildLevel();
          Player::AddPlayers();
          Player::SpawnPlayer(PLAYER_ONE);
          if (!singlePlayer)
            Player::SpawnPlayer(PLAYER_TWO);
          Sound::PlaySound("Theme");
        }
        else if (event.key.keysym.sym == SDLK_1)
          singlePlayer = !singlePlayer;
        else if (event.key.keysym.sym == SDLK_2)
          gamestate = STATE_CONTROLS;
        else if (event.key.keysym.sym == SDLK_3)
          gamestate = STATE_CREDITS;
      }
    }
    else if (gamestate == STATE_CONTROLS || gamestate == STATE_CREDITS)
    {
      if (event.type == SDL_KEYDOWN)
        if (event.key.keysym.sym == SDLK_RETURN)
          gamestate = STATE_MENU;
    }
    else if (gamestate == STATE_GAMEOVER || gamestate == STATE_VICTORY)
    {
      if (event.type == SDL_KEYDOWN)
        if (event.key.keysym.sym == SDLK_RETURN)
        {
          gamestate = STATE_MENU;
          Player::RemovePlayers();
          Boss::RemoveBoss();
          Object::RemoveAll();
          Sound::PlaySound("Intro");
        }
    }
    else if (gamestate == STATE_PLAYING)
    {
      Player::ProcessInput(event);

      if (event.type == SDL_KEYDOWN)
      {
        if (event.key.keysym.sym == SDLK_RSHIFT)
          singlePlayer = false;
        if (event.key.keysym.sym == SDLK_RETURN)
          gamestate = STATE_PAUSED;
      }
    }
    else if (gamestate == STATE_PAUSED)
    {
      if (event.type == SDL_KEYDOWN)
        if (event.key.keysym.sym == SDLK_RETURN)
          gamestate = STATE_PLAYING;
    }

    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_ESCAPE)
        done = true;
      if (event.key.keysym.sym == SDLK_TAB)
        showDebug = !showDebug;
    }

    if (event.type == SDL_QUIT)
      done = true;
  }
}

void Game::OnUpdate()
{
  float deltaTime = timer.getDeltaTime();

  if (gamestate == STATE_PLAYING)
  {
    Object::UpdateObjects(deltaTime);
    Level::LevelOne.Update(deltaTime);
    starfield.Update(deltaTime);

    if (singlePlayer)
    {
      if (Player::Players[0].lives <= 0)
      {
        gamestate = STATE_GAMEOVER;
        Sound::PlaySound("GameOver");
      }
    }
    else
    {
      if (Player::Players[0].lives + Player::Players[1].lives <= 0)
      {
        gamestate = STATE_GAMEOVER;
        Sound::PlaySound("GameOver");
      }
    }

    if (Boss::FinalBoss.spawned && Boss::FinalBoss.killed)
    {
      gamestate = STATE_VICTORY;
      Sound::PlaySound("Victory");
    }
  }

  ++frame;
}

void Game::OnRender()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  if (gamestate == STATE_MENU)
  {
    DrawTitle();
  }
  else if (gamestate == STATE_CONTROLS)
  {
    DrawControls();
  }
  else if (gamestate == STATE_CREDITS)
  {
    DrawCredits();
  }
  else if (gamestate == STATE_PLAYING)
  {
    Object::RenderObjects(renderer);
    DrawHUD();
  }
  else if (gamestate == STATE_PAUSED)
  {
    Object::RenderObjects(renderer);
    DrawHUD();
    DrawPaused();
  }
  else if (gamestate == STATE_GAMEOVER)
  {
    Object::RenderObjects(renderer);
    DrawHUD();
    DrawGameOver();
  }
  else if (gamestate == STATE_VICTORY)
  {
    Object::RenderObjects(renderer);
    DrawHUD();
    DrawVictory();
  }

  if (showDebug)
    DrawDebug();

  SDL_RenderPresent(renderer);
}

// helper functions to draw various parts of the game

void Game::DrawHUD()
{
  // player 1 HUD
  SDL_Rect health1 = {20, ScreenHeight - 25, 200, 10};
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
  SDL_RenderFillRect(renderer, &health1);

  if (Player::Players[0].ship != NULL)
  {
    health1.w = Player::Players[0].ship->health * 2;
    SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
    SDL_RenderFillRect(renderer, &health1);
  }

  for (int i = 0; i < Player::Players[0].lives; ++i)
  {
    SDL_Rect box = {(i + 1) * 20, ScreenHeight - 45, 10, 10};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &box);
  }

  // player 2 HUD
  if (!singlePlayer)
  {
    SDL_Rect health2 = {ScreenWidth - 220, ScreenHeight - 25, 200, 10};
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &health2);

    if (Player::Players[1].ship != NULL)
    {
      health2.x = ScreenWidth - 220 + (PlayerHealth - Player::Players[1].ship->health) * 2;
      health2.w = Player::Players[1].ship->health * 2;
      SDL_SetRenderDrawColor(renderer, 50, 50, 200, 255);
      SDL_RenderFillRect(renderer, &health2);
    }

    for (int i = 0; i < Player::Players[1].lives; ++i)
    {
      SDL_Rect box = {ScreenWidth - 10 - (i + 1) * 20, ScreenHeight - 45, 10, 10};
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderFillRect(renderer, &box);
    }
  }

  // display score
  char buffer[20];
  sprintf(buffer, "%d", Player::Players[0].score);
  Texture::DrawText(renderer, "SCORE", 10, ScreenWidth / 2, ScreenHeight - 35, 255, 255, 255);
  Texture::DrawText(renderer, buffer,  14, ScreenWidth / 2, ScreenHeight - 20, 255, 255, 255);

  // boss HUD
  if (Boss::FinalBoss.spawned && !Boss::FinalBoss.killed)
  {
    int barWidth = ScreenWidth - 40;
    SDL_Rect boss = {20, 20, barWidth, 10};
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &boss);

    if (Boss::FinalBoss.boss != NULL)
    {
      boss.w = (Sint16)(1.0f * Boss::FinalBoss.boss->health / BossHealth * barWidth);
      SDL_SetRenderDrawColor(renderer, 50, 200, 50, 255);
      SDL_RenderFillRect(renderer, &boss);
    }
  }
}

void Game::DrawTitle()
{
  Texture* titleTexture = Texture::TextureList["Title"];
  SDL_Rect titleRect = {ScreenWidth / 2 - titleTexture->width / 2, ScreenHeight / 2 - titleTexture->height / 2 - 100, titleTexture->width, titleTexture->height};
  SDL_RenderCopy(renderer, titleTexture->textures[0], NULL, &titleRect);

  Texture::DrawText(renderer, "Press ENTER to Start", 25, ScreenWidth / 2, ScreenHeight / 2 + 75, 255, 255, 255);

  if (singlePlayer)
    Texture::DrawText(renderer, "1-Player", 20, ScreenWidth / 2, ScreenHeight / 2 + 100, 255, 255, 255);
  else
    Texture::DrawText(renderer, "2-Player", 20, ScreenWidth / 2, ScreenHeight / 2 + 100, 255, 255, 255);

  Texture::DrawText(renderer, "Players",  20, ScreenWidth / 2 - 100, ScreenHeight / 2 + 150, 255, 255, 255);
  Texture::DrawText(renderer, "(1)",      20, ScreenWidth / 2 + 100, ScreenHeight / 2 + 150, 255, 255, 255);
  Texture::DrawText(renderer, "Controls", 20, ScreenWidth / 2 - 100, ScreenHeight / 2 + 175, 255, 255, 255);
  Texture::DrawText(renderer, "(2)",      20, ScreenWidth / 2 + 100, ScreenHeight / 2 + 175, 255, 255, 255);
  Texture::DrawText(renderer, "Credits",  20, ScreenWidth / 2 - 100, ScreenHeight / 2 + 200, 255, 255, 255);
  Texture::DrawText(renderer, "(3)",      20, ScreenWidth / 2 + 100, ScreenHeight / 2 + 200, 255, 255, 255);
  Texture::DrawText(renderer, "Debug",    20, ScreenWidth / 2 - 100, ScreenHeight / 2 + 225, 255, 255, 255);
  Texture::DrawText(renderer, "(Tab)",    20, ScreenWidth / 2 + 100, ScreenHeight / 2 + 225, 255, 255, 255);
  Texture::DrawText(renderer, "Exit",     20, ScreenWidth / 2 - 100, ScreenHeight / 2 + 250, 255, 255, 255);
  Texture::DrawText(renderer, "(Esc)",    20, ScreenWidth / 2 + 100, ScreenHeight / 2 + 250, 255, 255, 255);
}

void Game::DrawControls()
{
  Texture::DrawText(renderer, "CONTROLS", 35, ScreenWidth / 2,  40, 255, 255, 255);

  Texture* keyTexture = Texture::TextureList["Keyboard"];
  SDL_Rect keyRect = {ScreenWidth / 2 - keyTexture->width / 2, ScreenHeight / 2 - keyTexture->height / 2, keyTexture->width, keyTexture->height};
  SDL_RenderCopy(renderer, keyTexture->textures[0], NULL, &keyRect);

  Texture::DrawText(renderer, "Press ENTER to Return to Main Menu", 16, ScreenWidth / 2, ScreenHeight - 40, 255, 255, 255);
}

void Game::DrawCredits()
{
  Texture::DrawText(renderer, "CREDITS",      35, ScreenWidth / 2,  40, 255, 255, 255);
  Texture::DrawText(renderer, "Programming",  15, ScreenWidth / 2, 150, 255, 255, 255);
  Texture::DrawText(renderer, "Jason Norris", 25, ScreenWidth / 2, 170, 255, 255, 255);
  Texture::DrawText(renderer, "Artwork",      15, ScreenWidth / 2, 250, 255, 255, 255);
  Texture::DrawText(renderer, "Jason Norris", 25, ScreenWidth / 2, 270, 255, 255, 255);
  Texture::DrawText(renderer, "Music",        15, ScreenWidth / 2, 350, 255, 255, 255);
  Texture::DrawText(renderer, "Andy Cubrich", 25, ScreenWidth / 2, 370, 255, 255, 255);
  Texture::DrawText(renderer, "Press ENTER to Return to Main Menu", 16, ScreenWidth / 2, ScreenHeight - 40, 255, 255, 255);
}

void Game::DrawPaused()
{
  SDL_Rect rect = {0, 0, ScreenWidth, ScreenHeight};
  Texture::FillAlphaRect(renderer, rect, 0, 0, 0, 128);
  Texture::DrawText(renderer, "PAUSED", 30, ScreenWidth / 2, ScreenHeight / 2, 255, 255, 255);
}

void Game::DrawGameOver()
{
  SDL_Rect rect = {0, 0, ScreenWidth, ScreenHeight};
  Texture::FillAlphaRect(renderer, rect, 255, 0, 0, 128);
  Texture::DrawText(renderer, "FAILURE", 95, ScreenWidth / 2, ScreenHeight / 2, 255, 0, 0);
  Texture::DrawText(renderer, "Press ENTER to Return to Main Menu", 16, ScreenWidth / 2, ScreenHeight / 2 + 50, 255, 0, 0);
}

void Game::DrawVictory()
{
  SDL_Rect rect = {0, 0, ScreenWidth, ScreenHeight};
  Texture::FillAlphaRect(renderer, rect, 0, 255, 0, 128);
  Texture::DrawText(renderer, "SUCCESS", 95, ScreenWidth / 2, ScreenHeight / 2, 0, 255, 0);
  Texture::DrawText(renderer, "Press ENTER to Return to Main Menu", 16, ScreenWidth / 2, ScreenHeight / 2 + 50, 0, 255, 0);
}

void Game::DrawDebug()
{
  char buffer[15];
  sprintf(buffer, "FPS: %d", (int)(frame / timer.getStartTime()));
  Texture::DrawText(renderer, buffer, 14, 10, 10, 255, 255, 255, false);
  sprintf(buffer, "Objects: %d", Object::ObjectList.size());
  Texture::DrawText(renderer, buffer, 14, 10, 30, 255, 255, 255, false);
}
