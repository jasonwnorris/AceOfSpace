// Game.cpp

// STL Includes
#include <sstream>
// AOS Includes
#include "Game.hpp"
#include "Config.hpp"
#include "Sound.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "Boss.hpp"
#include "Graphics.hpp"

const SDL_Color Game::c_White = { 255, 255, 255, 255 };
const SDL_Color Game::c_Green = { 0, 255, 0, 255 };
const SDL_Color Game::c_Red = { 255, 0, 0, 255 };

Game::Game()
{
  SDL_Log("Initializing SDL... ");
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL: %s", SDL_GetError());
    exit(1);
  }
  SDL_Log("complete!");

  SDL_ShowCursor(SDL_DISABLE);

  SDL_Log("Initializing TTF... ");
  if (TTF_Init() < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize TTF: %s", SDL_GetError());
    exit(1);
  }
  SDL_Log("complete!");

  SDL_Log("Initializing audio... ");
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize audio: %s", SDL_GetError());
    exit(1);
  }
  SDL_Log("complete!");

  SDL_Log("Initializing window... ");
  window = SDL_CreateWindow("Ace of Space", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, 0);

  if (window == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize the window.");
    exit(1);
  }
  SDL_Log("complete!");

  SDL_Log("Initializing renderer... ");
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize the renderer.");
    exit(1);
  }
  SDL_Log("complete!");

  done = false;
  interval = 0.25f;
  elapsedTime = 0.0f;
  frameCount = 0;
  framesPerSecond = 0;
  objectCount = 0;
  gamestate = STATE_MENU;
  singlePlayer = true;
  showDebug = false;
}

Game::~Game()
{
  SDL_Log("Closing audio... ");
  Mix_CloseAudio();
  SDL_Log("complete!");

  SDL_Log("Closing TTF... ");
  TTF_Quit();
  SDL_Log("complete!");

  SDL_Log("Closing SDL... ");
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  SDL_Log("complete!");

  SDL_Log("Game ended successfully!");
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
  const std::string filename = "resources/framd.ttf";
  font10.Load(renderer, filename, 10);
  font14.Load(renderer, filename, 14);
  font16.Load(renderer, filename, 16);
  font20.Load(renderer, filename, 20);
  font25.Load(renderer, filename, 25);
  font35.Load(renderer, filename, 35);

  Texture::LoadTextures(renderer);
  Sound::LoadSounds();
  Sound::PlaySound("Intro");
}

void Game::OnEnd()
{
  font10.Unload();
  font14.Unload();
  font16.Unload();
  font20.Unload();
  font25.Unload();
  font35.Unload();

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
        {
          singlePlayer = !singlePlayer;
        }
        else if (event.key.keysym.sym == SDLK_2)
        {
          gamestate = STATE_CONTROLS;
        }
        else if (event.key.keysym.sym == SDLK_3)
        {
          gamestate = STATE_CREDITS;
        }
      }
    }
    else if (gamestate == STATE_CONTROLS || gamestate == STATE_CREDITS)
    {
      if (event.type == SDL_KEYDOWN)
      {
        if (event.key.keysym.sym == SDLK_RETURN)
        {
          gamestate = STATE_MENU;
        }
      }
    }
    else if (gamestate == STATE_GAMEOVER || gamestate == STATE_VICTORY)
    {
      if (event.type == SDL_KEYDOWN)
      {
        if (event.key.keysym.sym == SDLK_RETURN)
        {
          gamestate = STATE_MENU;
          Player::RemovePlayers();
          Boss::RemoveBoss();
          Object::RemoveAll();
          Sound::PlaySound("Intro");
        }
      }
    }
    else if (gamestate == STATE_PLAYING)
    {
      Player::ProcessInput(event);

      if (event.type == SDL_KEYDOWN)
      {
        if (event.key.keysym.sym == SDLK_RSHIFT)
        {
          singlePlayer = false;
        }
        if (event.key.keysym.sym == SDLK_RETURN)
        {
          gamestate = STATE_PAUSED;
        }
      }
    }
    else if (gamestate == STATE_PAUSED)
    {
      if (event.type == SDL_KEYDOWN)
      {
        if (event.key.keysym.sym == SDLK_RETURN)
        {
          gamestate = STATE_PLAYING;
        }
      }
    }

    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        done = true;
      }
      if (event.key.keysym.sym == SDLK_TAB)
      {
        showDebug = !showDebug;
      }
    }

    if (event.type == SDL_QUIT)
    {
      done = true;
    }
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

  ++frameCount;
  elapsedTime += deltaTime;
  if (elapsedTime >= interval)
  {
    framesPerSecond = (int)(frameCount / interval);
    objectCount = (int)Object::ObjectList.size();
    elapsedTime = 0.0f;
    frameCount = 0;
  }
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
  {
    DrawDebug();
  }

  SDL_RenderPresent(renderer);
}

void Game::DrawHUD()
{
  // player 1 HUD
  SDL_Rect health1 = {20, ScreenHeight - 25, 200, 10};
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
  SDL_RenderFillRect(renderer, &health1);

  if (Player::Players[0].ship != nullptr)
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

    if (Player::Players[1].ship != nullptr)
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
  std::stringstream ss;
  ss << Player::Players[0].score;
  Graphics::DrawText(renderer, font10, "SCORE", ScreenWidth / 2, ScreenHeight - 35, c_White);
  Graphics::DrawText(renderer, font14, ss.str(), ScreenWidth / 2, ScreenHeight - 20, c_White);

  // boss HUD
  if (Boss::FinalBoss.spawned && !Boss::FinalBoss.killed)
  {
    int barWidth = ScreenWidth - 40;
    SDL_Rect boss = {20, 20, barWidth, 10};
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &boss);

    if (Boss::FinalBoss.boss != nullptr)
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
  SDL_Rect titleRect = { ScreenWidth / 2 - titleTexture->width / 2, ScreenHeight / 2 - titleTexture->height / 2 - 100, titleTexture->width, titleTexture->height };
  SDL_RenderCopy(renderer, titleTexture->textures[0], nullptr, &titleRect);

  Graphics::DrawText(renderer, font25, "Press ENTER to Start", ScreenWidth / 2, ScreenHeight / 2 + 75, c_White);
  Graphics::DrawText(renderer, font20, (singlePlayer ? "1-Player" : "2-Player"), ScreenWidth / 2, ScreenHeight / 2 + 100, c_White);

  Graphics::DrawText(renderer, font20, "Players", ScreenWidth / 2 - 100, ScreenHeight / 2 + 150, c_White);
  Graphics::DrawText(renderer, font20, "(1)", ScreenWidth / 2 + 100, ScreenHeight / 2 + 150, c_White);

  Graphics::DrawText(renderer, font20, "Controls", ScreenWidth / 2 - 100, ScreenHeight / 2 + 175, c_White);
  Graphics::DrawText(renderer, font20, "(2)", ScreenWidth / 2 + 100, ScreenHeight / 2 + 175, c_White);

  Graphics::DrawText(renderer, font20, "Credits", ScreenWidth / 2 - 100, ScreenHeight / 2 + 200, c_White);
  Graphics::DrawText(renderer, font20, "(3)", ScreenWidth / 2 + 100, ScreenHeight / 2 + 200, c_White);

  Graphics::DrawText(renderer, font20, "Debug", ScreenWidth / 2 - 100, ScreenHeight / 2 + 225, c_White);
  Graphics::DrawText(renderer, font20, "(Tab)", ScreenWidth / 2 + 100, ScreenHeight / 2 + 225, c_White);

  Graphics::DrawText(renderer, font20, "Exit", ScreenWidth / 2 - 100, ScreenHeight / 2 + 250, c_White);
  Graphics::DrawText(renderer, font20, "(Esc)", ScreenWidth / 2 + 100, ScreenHeight / 2 + 250, c_White);
}

void Game::DrawControls()
{
  Texture* keyTexture = Texture::TextureList["Keyboard"];
  SDL_Rect keyRect = { ScreenWidth / 2 - keyTexture->width / 2, ScreenHeight / 2 - keyTexture->height / 2, keyTexture->width, keyTexture->height };
  SDL_RenderCopy(renderer, keyTexture->textures[0], nullptr, &keyRect);

  Graphics::DrawText(renderer, font35, "CONTROLS", ScreenWidth / 2, 40, c_White);
  Graphics::DrawText(renderer, font16, "Press ENTER to Return to Main Menu", ScreenWidth / 2, ScreenHeight - 40, c_White);
}

void Game::DrawCredits()
{
  Graphics::DrawText(renderer, font35, "CREDITS", ScreenWidth / 2, 40, c_White);

  Graphics::DrawText(renderer, font14, "Programming", ScreenWidth / 2, 150, c_White);
  Graphics::DrawText(renderer, font25, "Jason Norris", ScreenWidth / 2, 170, c_White);

  Graphics::DrawText(renderer, font14, "Programming", ScreenWidth / 2, 250, c_White);
  Graphics::DrawText(renderer, font25, "Jason Norris", ScreenWidth / 2, 270, c_White);

  Graphics::DrawText(renderer, font14, "Programming", ScreenWidth / 2, 350, c_White);
  Graphics::DrawText(renderer, font25, "Jason Norris", ScreenWidth / 2, 370, c_White);

  Graphics::DrawText(renderer, font16, "Press ENTER to Return to Main Menu", ScreenWidth / 2, ScreenHeight - 40, c_White);
}

void Game::DrawPaused()
{
  SDL_Rect rect = {0, 0, ScreenWidth, ScreenHeight};
  Graphics::FillAlphaRect(renderer, rect, 0, 0, 0, 128);
  Graphics::DrawText(renderer, font35, "PAUSED", ScreenWidth / 2, ScreenHeight / 2, c_White);
}

void Game::DrawGameOver()
{
  SDL_Rect rect = {0, 0, ScreenWidth, ScreenHeight};
  Graphics::FillAlphaRect(renderer, rect, 255, 0, 0, 128);
  Graphics::DrawText(renderer, font35, "FAILURE", ScreenWidth / 2, ScreenHeight / 2, c_Red);
  Graphics::DrawText(renderer, font14, "Press ENTER to Return to Main Menu", ScreenWidth / 2, ScreenHeight / 2 + 50, c_Red);
}

void Game::DrawVictory()
{
  SDL_Rect rect = {0, 0, ScreenWidth, ScreenHeight};
  Graphics::FillAlphaRect(renderer, rect, 0, 255, 0, 128);
  Graphics::DrawText(renderer, font35, "SUCCESS", ScreenWidth / 2, ScreenHeight / 2, c_Green);
  Graphics::DrawText(renderer, font14, "Press ENTER to Return to Main Menu", ScreenWidth / 2, ScreenHeight / 2 + 50, c_Green);
}

void Game::DrawDebug()
{
  std::stringstream ss1;
  ss1 << "FPS: " << framesPerSecond;
  Graphics::DrawText(renderer, font14, ss1.str(), 10, 10, c_White, false);
  std::stringstream ss2;
  ss2 << "Objects: " << objectCount;
  Graphics::DrawText(renderer, font14, ss2.str(), 10, 30, c_White, false);
}
