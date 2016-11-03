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
  m_Window = SDL_CreateWindow("Ace of Space", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, 0);

  if (m_Window == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize the window.");
    exit(1);
  }
  SDL_Log("complete!");

  SDL_Log("Initializing renderer... ");
  m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

  if (m_Renderer == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize the renderer.");
    exit(1);
  }
  SDL_Log("complete!");

  m_IsDone = false;
  m_Interval = 0.25f;
  m_ElapsedTime = 0.0f;
  m_FrameCount = 0;
  m_FramesPerSecond = 0;
  m_ObjectCount = 0;
  m_State = STATE_MENU;
  m_IsSinglePlayer = true;
  m_IsDebugShown = false;
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
  SDL_DestroyRenderer(m_Renderer);
  SDL_DestroyWindow(m_Window);
  SDL_Quit();
  SDL_Log("complete!");

  SDL_Log("Game ended successfully!");
}

void Game::OnExecute()
{
  OnStart();

  while (!m_IsDone)
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
  m_Font10.Load(m_Renderer, filename, 10, TTF_STYLE_NORMAL, TTF_HINTING_LIGHT);
  m_Font14.Load(m_Renderer, filename, 14, TTF_STYLE_NORMAL, TTF_HINTING_LIGHT);
  m_Font16.Load(m_Renderer, filename, 16, TTF_STYLE_NORMAL, TTF_HINTING_LIGHT);
  m_Font20.Load(m_Renderer, filename, 20, TTF_STYLE_NORMAL, TTF_HINTING_LIGHT);
  m_Font25.Load(m_Renderer, filename, 25, TTF_STYLE_NORMAL, TTF_HINTING_LIGHT);
  m_Font35.Load(m_Renderer, filename, 35, TTF_STYLE_NORMAL, TTF_HINTING_LIGHT);

  Texture::LoadTextures(m_Renderer);
  Sound::LoadSounds();
  Sound::PlaySound("Intro");
}

void Game::OnEnd()
{
  m_Font10.Unload();
  m_Font14.Unload();
  m_Font16.Unload();
  m_Font20.Unload();
  m_Font25.Unload();
  m_Font35.Unload();

  Texture::UnloadTextures();
  Sound::UnloadSounds();
  Player::RemovePlayers();
  Object::RemoveAll();
}

void Game::OnThink()
{
  while (SDL_PollEvent(&m_Event))
  {
    if (m_State == STATE_MENU)
    {
      if (m_Event.type == SDL_KEYDOWN)
      {
        if (m_Event.key.keysym.sym == SDLK_RETURN)
        {
          m_State = STATE_PLAYING;
          Level::LevelOne.BuildLevel();
          Player::AddPlayers();
          Player::SpawnPlayer(PLAYER_ONE);
          if (!m_IsSinglePlayer)
          {
            Player::SpawnPlayer(PLAYER_TWO);
          }
          Sound::PlaySound("Theme");
        }
        else if (m_Event.key.keysym.sym == SDLK_1)
        {
          m_IsSinglePlayer = !m_IsSinglePlayer;
        }
        else if (m_Event.key.keysym.sym == SDLK_2)
        {
          m_State = STATE_CONTROLS;
        }
        else if (m_Event.key.keysym.sym == SDLK_3)
        {
          m_State = STATE_CREDITS;
        }
      }
    }
    else if (m_State == STATE_CONTROLS || m_State == STATE_CREDITS)
    {
      if (m_Event.type == SDL_KEYDOWN)
      {
        if (m_Event.key.keysym.sym == SDLK_RETURN)
        {
          m_State = STATE_MENU;
        }
      }
    }
    else if (m_State == STATE_GAMEOVER || m_State == STATE_VICTORY)
    {
      if (m_Event.type == SDL_KEYDOWN)
      {
        if (m_Event.key.keysym.sym == SDLK_RETURN)
        {
          m_State = STATE_MENU;
          Player::RemovePlayers();
          Boss::RemoveBoss();
          Object::RemoveAll();
          Sound::PlaySound("Intro");
        }
      }
    }
    else if (m_State == STATE_PLAYING)
    {
      Player::ProcessInput(m_Event);

      if (m_Event.type == SDL_KEYDOWN)
      {
        if (m_Event.key.keysym.sym == SDLK_RSHIFT)
        {
          m_IsSinglePlayer = false;
        }
        if (m_Event.key.keysym.sym == SDLK_RETURN)
        {
          m_State = STATE_PAUSED;
        }
      }
    }
    else if (m_State == STATE_PAUSED)
    {
      if (m_Event.type == SDL_KEYDOWN)
      {
        if (m_Event.key.keysym.sym == SDLK_RETURN)
        {
          m_State = STATE_PLAYING;
        }
      }
    }

    if (m_Event.type == SDL_KEYDOWN)
    {
      if (m_Event.key.keysym.sym == SDLK_ESCAPE)
      {
        m_IsDone = true;
      }
      if (m_Event.key.keysym.sym == SDLK_TAB)
      {
        m_IsDebugShown = !m_IsDebugShown;
      }
    }

    if (m_Event.type == SDL_QUIT)
    {
      m_IsDone = true;
    }
  }
}

void Game::OnUpdate()
{
  float deltaTime = m_Timer.GetDeltaTime();

  if (m_State == STATE_PLAYING)
  {
    Object::UpdateObjects(deltaTime);
    Level::LevelOne.Update(deltaTime);
    m_Starfield.Update(deltaTime);

    if (m_IsSinglePlayer)
    {
      if (Player::Players[0].m_Lives <= 0)
      {
        m_State = STATE_GAMEOVER;
        Sound::PlaySound("GameOver");
      }
    }
    else
    {
      if (Player::Players[0].m_Lives + Player::Players[1].m_Lives <= 0)
      {
        m_State = STATE_GAMEOVER;
        Sound::PlaySound("GameOver");
      }
    }

    if (Boss::FinalBoss.m_IsSpawned && Boss::FinalBoss.m_IsKilled)
    {
      m_State = STATE_VICTORY;
      Sound::PlaySound("Victory");
    }
  }

  ++m_FrameCount;
  m_ElapsedTime += deltaTime;
  if (m_ElapsedTime >= m_Interval)
  {
    m_FramesPerSecond = (int)(m_FrameCount / m_Interval);
    m_ObjectCount = (int)Object::ObjectList.size();
    m_ElapsedTime = 0.0f;
    m_FrameCount = 0;
  }
}

void Game::OnRender()
{
  SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_Renderer);

  if (m_State == STATE_MENU)
  {
    DrawTitle();
  }
  else if (m_State == STATE_CONTROLS)
  {
    DrawControls();
  }
  else if (m_State == STATE_CREDITS)
  {
    DrawCredits();
  }
  else if (m_State == STATE_PLAYING)
  {
    Object::RenderObjects(m_Renderer);
    DrawHUD();
  }
  else if (m_State == STATE_PAUSED)
  {
    Object::RenderObjects(m_Renderer);
    DrawHUD();
    DrawPaused();
  }
  else if (m_State == STATE_GAMEOVER)
  {
    Object::RenderObjects(m_Renderer);
    DrawHUD();
    DrawGameOver();
  }
  else if (m_State == STATE_VICTORY)
  {
    Object::RenderObjects(m_Renderer);
    DrawHUD();
    DrawVictory();
  }

  if (m_IsDebugShown)
  {
    DrawDebug();
  }

  SDL_RenderPresent(m_Renderer);
}

void Game::DrawHUD()
{
  // player 1 HUD
  SDL_Rect health1 = {20, ScreenHeight - 25, 200, 10};
  SDL_SetRenderDrawColor(m_Renderer, 50, 50, 50, 255);
  SDL_RenderFillRect(m_Renderer, &health1);

  if (Player::Players[0].m_Ship != nullptr)
  {
    health1.w = Player::Players[0].m_Ship->m_Health * 2;
    SDL_SetRenderDrawColor(m_Renderer, 200, 50, 50, 255);
    SDL_RenderFillRect(m_Renderer, &health1);
  }

  for (int i = 0; i < Player::Players[0].m_Lives; ++i)
  {
    SDL_Rect box = {(i + 1) * 20, ScreenHeight - 45, 10, 10};
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_Renderer, &box);
  }

  // player 2 HUD
  if (!m_IsSinglePlayer)
  {
    SDL_Rect health2 = {ScreenWidth - 220, ScreenHeight - 25, 200, 10};
    SDL_SetRenderDrawColor(m_Renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(m_Renderer, &health2);

    if (Player::Players[1].m_Ship != nullptr)
    {
      health2.x = ScreenWidth - 220 + (PlayerHealth - Player::Players[1].m_Ship->m_Health) * 2;
      health2.w = Player::Players[1].m_Ship->m_Health * 2;
      SDL_SetRenderDrawColor(m_Renderer, 50, 50, 200, 255);
      SDL_RenderFillRect(m_Renderer, &health2);
    }

    for (int i = 0; i < Player::Players[1].m_Lives; ++i)
    {
      SDL_Rect box = {ScreenWidth - 10 - (i + 1) * 20, ScreenHeight - 45, 10, 10};
      SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
      SDL_RenderFillRect(m_Renderer, &box);
    }
  }

  // display score
  std::stringstream ss;
  ss << Player::Players[0].m_Score;
  Graphics::DrawText(m_Renderer, m_Font10, "SCORE", ScreenWidth / 2, ScreenHeight - 35, c_White);
  Graphics::DrawText(m_Renderer, m_Font16, ss.str(), ScreenWidth / 2, ScreenHeight - 20, c_White);

  // boss HUD
  if (Boss::FinalBoss.m_IsSpawned && !Boss::FinalBoss.m_IsKilled)
  {
    int barWidth = ScreenWidth - 40;
    SDL_Rect boss = {20, 20, barWidth, 10};
    SDL_SetRenderDrawColor(m_Renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(m_Renderer, &boss);

    if (Boss::FinalBoss.m_Boss != nullptr)
    {
      boss.w = (Sint16)(1.0f * Boss::FinalBoss.m_Boss->m_Health / BossHealth * barWidth);
      SDL_SetRenderDrawColor(m_Renderer, 50, 200, 50, 255);
      SDL_RenderFillRect(m_Renderer, &boss);
    }
  }
}

void Game::DrawTitle()
{
  Texture* titleTexture = Texture::TextureList["Title"];
  SDL_Rect titleRect = { ScreenWidth / 2 - titleTexture->m_Width / 2, ScreenHeight / 2 - titleTexture->m_Height / 2 - 100, titleTexture->m_Width, titleTexture->m_Height };
  SDL_RenderCopy(m_Renderer, titleTexture->m_Textures[0], nullptr, &titleRect);

  Graphics::DrawText(m_Renderer, m_Font25, "Press ENTER to Start", ScreenWidth / 2, ScreenHeight / 2 + 75, c_White);
  Graphics::DrawText(m_Renderer, m_Font20, (m_IsSinglePlayer ? "1-Player" : "2-Player"), ScreenWidth / 2, ScreenHeight / 2 + 100, c_White);

  Graphics::DrawText(m_Renderer, m_Font20, "Players", ScreenWidth / 2 - 100, ScreenHeight / 2 + 150, c_White);
  Graphics::DrawText(m_Renderer, m_Font20, "(1)", ScreenWidth / 2 + 100, ScreenHeight / 2 + 150, c_White);

  Graphics::DrawText(m_Renderer, m_Font20, "Controls", ScreenWidth / 2 - 100, ScreenHeight / 2 + 175, c_White);
  Graphics::DrawText(m_Renderer, m_Font20, "(2)", ScreenWidth / 2 + 100, ScreenHeight / 2 + 175, c_White);

  Graphics::DrawText(m_Renderer, m_Font20, "Credits", ScreenWidth / 2 - 100, ScreenHeight / 2 + 200, c_White);
  Graphics::DrawText(m_Renderer, m_Font20, "(3)", ScreenWidth / 2 + 100, ScreenHeight / 2 + 200, c_White);

  Graphics::DrawText(m_Renderer, m_Font20, "Debug", ScreenWidth / 2 - 100, ScreenHeight / 2 + 225, c_White);
  Graphics::DrawText(m_Renderer, m_Font20, "(Tab)", ScreenWidth / 2 + 100, ScreenHeight / 2 + 225, c_White);

  Graphics::DrawText(m_Renderer, m_Font20, "Exit", ScreenWidth / 2 - 100, ScreenHeight / 2 + 250, c_White);
  Graphics::DrawText(m_Renderer, m_Font20, "(Esc)", ScreenWidth / 2 + 100, ScreenHeight / 2 + 250, c_White);
}

void Game::DrawControls()
{
  Texture* keyTexture = Texture::TextureList["Keyboard"];
  SDL_Rect keyRect = { ScreenWidth / 2 - keyTexture->m_Width / 2, ScreenHeight / 2 - keyTexture->m_Height / 2, keyTexture->m_Width, keyTexture->m_Height };
  SDL_RenderCopy(m_Renderer, keyTexture->m_Textures[0], nullptr, &keyRect);

  Graphics::DrawText(m_Renderer, m_Font35, "CONTROLS", ScreenWidth / 2, 40, c_White);
  Graphics::DrawText(m_Renderer, m_Font16, "Press ENTER to Return to Main Menu", ScreenWidth / 2, ScreenHeight - 40, c_White);
}

void Game::DrawCredits()
{
  Graphics::DrawText(m_Renderer, m_Font35, "CREDITS", ScreenWidth / 2, 40, c_White);

  Graphics::DrawText(m_Renderer, m_Font14, "Programming", ScreenWidth / 2, 150, c_White);
  Graphics::DrawText(m_Renderer, m_Font25, "Jason Norris", ScreenWidth / 2, 170, c_White);

  Graphics::DrawText(m_Renderer, m_Font14, "Programming", ScreenWidth / 2, 250, c_White);
  Graphics::DrawText(m_Renderer, m_Font25, "Jason Norris", ScreenWidth / 2, 270, c_White);

  Graphics::DrawText(m_Renderer, m_Font14, "Programming", ScreenWidth / 2, 350, c_White);
  Graphics::DrawText(m_Renderer, m_Font25, "Jason Norris", ScreenWidth / 2, 370, c_White);

  Graphics::DrawText(m_Renderer, m_Font16, "Press ENTER to Return to Main Menu", ScreenWidth / 2, ScreenHeight - 40, c_White);
}

void Game::DrawPaused()
{
  SDL_Rect rect = {0, 0, ScreenWidth, ScreenHeight};
  Graphics::FillAlphaRect(m_Renderer, rect, 0, 0, 0, 128);
  Graphics::DrawText(m_Renderer, m_Font35, "PAUSED", ScreenWidth / 2, ScreenHeight / 2, c_White);
}

void Game::DrawGameOver()
{
  SDL_Rect rect = {0, 0, ScreenWidth, ScreenHeight};
  Graphics::FillAlphaRect(m_Renderer, rect, 255, 0, 0, 128);
  Graphics::DrawText(m_Renderer, m_Font35, "FAILURE", ScreenWidth / 2, ScreenHeight / 2, c_Red);
  Graphics::DrawText(m_Renderer, m_Font14, "Press ENTER to Return to Main Menu", ScreenWidth / 2, ScreenHeight / 2 + 50, c_Red);
}

void Game::DrawVictory()
{
  SDL_Rect rect = {0, 0, ScreenWidth, ScreenHeight};
  Graphics::FillAlphaRect(m_Renderer, rect, 0, 255, 0, 128);
  Graphics::DrawText(m_Renderer, m_Font35, "SUCCESS", ScreenWidth / 2, ScreenHeight / 2, c_Green);
  Graphics::DrawText(m_Renderer, m_Font14, "Press ENTER to Return to Main Menu", ScreenWidth / 2, ScreenHeight / 2 + 50, c_Green);
}

void Game::DrawDebug()
{
  std::stringstream ss1;
  ss1 << "FPS: " << m_FramesPerSecond;
  Graphics::DrawText(m_Renderer, m_Font14, ss1.str(), 10, 10, c_White, false);
  std::stringstream ss2;
  ss2 << "Objects: " << m_ObjectCount;
  Graphics::DrawText(m_Renderer, m_Font14, ss2.str(), 10, 30, c_White, false);
}
