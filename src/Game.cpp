// Game.cpp

// STL Includes
#include <sstream>
// AOS Includes
#include "Config.hpp"
#include "Color.hpp"
#include "Game.hpp"
#include "Sound.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "PlayerIndex.hpp"
#include "Boss.hpp"
#include "Graphics.hpp"

Game::Game()
{
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
}

bool Game::Run()
{
  if (!OnStart())
  {
    return false;
  }

  while (!m_IsDone)
  {
    OnThink();
    OnUpdate();
    OnRender();
  }

  OnEnd();

  return true;
}

bool Game::OnStart()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }
  SDL_Log("Initializing SDL... complete!");

  if (TTF_Init() < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL_TTF: %s", SDL_GetError());
    return false;
  }
  SDL_Log("Initializing TTF... complete!");

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL_Mixer: %s", SDL_GetError());
    return false;
  }
  SDL_Log("Initializing audio... complete!");

  m_Window = SDL_CreateWindow("Ace of Space", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, c_ScreenWidth, c_ScreenHeight, 0);
  if (m_Window == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize the window.");
    return false;
  }
  SDL_Log("Initializing window... complete!");

  m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
  if (m_Renderer == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize the renderer.");
    return false;
  }
  SDL_Log("Initializing renderer... complete!");

  SDL_ShowCursor(SDL_DISABLE);
  SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);

  if (!m_Font10.Load(m_Renderer, c_FontFilename, 10, TTF_STYLE_NORMAL, TTF_HINTING_LIGHT) ||
      !m_Font14.Load(m_Renderer, c_FontFilename, 14, TTF_STYLE_NORMAL, TTF_HINTING_LIGHT) ||
      !m_Font16.Load(m_Renderer, c_FontFilename, 16, TTF_STYLE_NORMAL, TTF_HINTING_LIGHT) ||
      !m_Font20.Load(m_Renderer, c_FontFilename, 20, TTF_STYLE_NORMAL, TTF_HINTING_LIGHT) ||
      !m_Font25.Load(m_Renderer, c_FontFilename, 25, TTF_STYLE_NORMAL, TTF_HINTING_LIGHT) ||
      !m_Font35.Load(m_Renderer, c_FontFilename, 35, TTF_STYLE_NORMAL, TTF_HINTING_LIGHT))
  {
    return false;
  }

  if (!Texture::LoadTextures(m_Renderer) || !Sound::LoadSounds())
  {
    return false;
  }

  Sound::PlaySound("Intro");

  return true;
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

  Mix_CloseAudio();
  SDL_Log("Closing SDL_Mixer... complete!");

  TTF_Quit();
  SDL_Log("Closing SDL_TTF... complete!");

  SDL_DestroyRenderer(m_Renderer);
  SDL_DestroyWindow(m_Window);
  SDL_Quit();
  SDL_Log("Closing SDL... complete!");
}

void Game::OnThink()
{
  while (SDL_PollEvent(&m_Event))
  {
    Uint32 type = m_Event.type;
    SDL_Keycode key = m_Event.key.keysym.sym;

    switch (type)
    {
      case SDL_QUIT:
        m_IsDone = true;
        break;
      case SDL_KEYDOWN:
        switch (key)
        {
          case SDLK_ESCAPE:
            m_IsDone = true;
            break;
          case SDLK_TAB:
            m_IsDebugShown = !m_IsDebugShown;
            break;
        }
        break;
    }

    switch (m_State)
    {
      case STATE_MENU:
        switch (type)
        {
          case SDL_KEYDOWN:
            switch (key)
            {
              case SDLK_RETURN:
                m_Level.BuildLevel();
                Player::AddPlayers();
                Player::SpawnPlayer(PLAYER_ONE);
                if (!m_IsSinglePlayer)
                {
                  Player::SpawnPlayer(PLAYER_TWO);
                }
                Sound::PlaySound("Theme");
                m_State = STATE_PLAYING;
                break;
              case SDLK_1:
                m_IsSinglePlayer = !m_IsSinglePlayer;
                break;
              case SDLK_2:
                m_State = STATE_CONTROLS;
                break;
              case SDLK_3:
                m_State = STATE_CREDITS;
                break;
            }
            break;
        }
        break;
      case STATE_GAMEOVER:
      case STATE_VICTORY:
        switch (type)
        {
          case SDL_KEYDOWN:
            switch (key)
            {
              case SDLK_RETURN:
                Player::RemovePlayers();
                Boss::RemoveBoss();
                Object::RemoveAll();
                Sound::PlaySound("Intro");
                m_State = STATE_MENU;
                break;
            }
            break;
        }
        break;
      case STATE_CONTROLS:
      case STATE_CREDITS:
        switch (type)
        {
          case SDL_KEYDOWN:
            switch (key)
            {
              case SDLK_RETURN:
                m_State = STATE_MENU;
                break;
            }
            break;
        }
        break;
      case STATE_PLAYING:
        Player::ProcessInput(type, key);
        switch (type)
        {
          case SDL_KEYDOWN:
            switch (key)
            {
              case SDLK_RSHIFT:
                m_IsSinglePlayer = false;
                break;
              case SDLK_RETURN:
                m_State = STATE_PAUSED;
                break;
            }
            break;
        }
        break;
      case STATE_PAUSED:
        switch (type)
        {
          case SDL_KEYDOWN:
            switch (key)
            {
              case SDLK_RETURN:
                m_State = STATE_PLAYING;
                break;
            }
            break;
        }
        break;
    }
  }
}

void Game::OnUpdate()
{
  float deltaTime = m_Timer.GetDeltaTime();

  switch (m_State)
  {
    case STATE_PLAYING:
      Object::UpdateObjects(deltaTime);
      m_Level.Update(deltaTime);
      m_Starfield.Update(deltaTime);
      bool isSinglePlayerDead = m_IsSinglePlayer && Player::Players[0].GetLives()  <= 0;
      bool isTwoPlayerDead = !m_IsSinglePlayer && Player::Players[0].GetLives() + Player::Players[1].GetLives() <= 0;
      if (isSinglePlayerDead || isTwoPlayerDead)
      {
        Sound::PlaySound("GameOver");
        m_State = STATE_GAMEOVER;
      }
      if (Boss::FinalBoss.IsSpawned() && Boss::FinalBoss.IsKilled())
      {
        Sound::PlaySound("Victory");
        m_State = STATE_VICTORY;
      }
      break;
  }

  ++m_FrameCount;
  m_ElapsedTime += deltaTime;
  if (m_ElapsedTime >= m_Interval)
  {
    m_FramesPerSecond = static_cast<int>(m_FrameCount / m_Interval);
    m_ObjectCount = static_cast<int>(Object::ObjectList.size());
    m_ElapsedTime = 0.0f;
    m_FrameCount = 0;
  }
}

void Game::OnRender()
{
  SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_Renderer);

  switch (m_State)
  {
    case STATE_MENU:
      DrawTitle();
      break;
    case STATE_CONTROLS:
      DrawControls();
      break;  
    case STATE_CREDITS:
      DrawCredits();
      break;
    case STATE_PLAYING:
      Object::RenderObjects(m_Renderer);
      DrawHUD();
      break;
    case STATE_PAUSED:
      Object::RenderObjects(m_Renderer);
      DrawHUD();
      DrawPaused();
      break;
    case STATE_GAMEOVER:
      Object::RenderObjects(m_Renderer);
      DrawHUD();
      DrawGameOver();
      break;
    case STATE_VICTORY:
      Object::RenderObjects(m_Renderer);
      DrawHUD();
      DrawVictory();
      break;
  }

  if (m_IsDebugShown)
  {
    DrawDebug();
  }

  SDL_RenderPresent(m_Renderer);
}

void Game::DrawHUD()
{
  // Player 1 HUD
  SDL_Rect health1 = { 20, c_ScreenHeight - 25, 200, 10 };
  Graphics::FillRectangle(m_Renderer, health1, Color::DarkGray);

  const PlayerShip* playerShip1 = Player::Players[0].GetPlayerShip();
  if (playerShip1 != nullptr)
  {
    health1.w = playerShip1->GetHealth() * 2;
    Graphics::FillRectangle(m_Renderer, health1, Color::DarkRed);
  }

  for (int i = 0; i < Player::Players[0].GetLives(); ++i)
  {
    SDL_Rect box = { (i + 1) * 20, c_ScreenHeight - 45, 10, 10 };
    Graphics::FillRectangle(m_Renderer, box, Color::White);
  }

  // Player 2 HUD
  if (!m_IsSinglePlayer)
  {
    SDL_Rect health2 = { c_ScreenWidth - 220, c_ScreenHeight - 25, 200, 10 };
    Graphics::FillRectangle(m_Renderer, health2, Color::DarkGray);

    const PlayerShip* playerShip2 = Player::Players[1].GetPlayerShip();
    if (playerShip2 != nullptr)
    {
      health2.x = c_ScreenWidth - 220 + (c_PlayerHealth - playerShip2->GetHealth()) * 2;
      health2.w = playerShip2->GetHealth() * 2;
      Graphics::FillRectangle(m_Renderer, health2, Color::DarkBlue);
    }

    for (int i = 0; i < Player::Players[1].GetLives(); ++i)
    {
      SDL_Rect box = { c_ScreenWidth - 10 - (i + 1) * 20, c_ScreenHeight - 45, 10, 10 };
      Graphics::FillRectangle(m_Renderer, box, Color::White);
    }
  }

  // Display Score
  std::stringstream ss;
  ss << Player::Players[0].GetScore();
  Graphics::DrawText(m_Renderer, m_Font10, "SCORE", c_HalfScreenWidth, c_ScreenHeight - 35, Color::White);
  Graphics::DrawText(m_Renderer, m_Font16, ss.str(), c_HalfScreenWidth, c_ScreenHeight - 20, Color::White);

  // Boss HUD
  if (Boss::FinalBoss.IsSpawned() && !Boss::FinalBoss.IsKilled())
  {
    int barWidth = c_ScreenWidth - 40;
    SDL_Rect boss = { 20, 20, barWidth, 10 };
    Graphics::FillRectangle(m_Renderer, boss, Color::DarkGray);

    const BossEnemy* bossEnemy = Boss::FinalBoss.GetBossEnemy();
    if (bossEnemy != nullptr)
    {
      boss.w = bossEnemy->GetHealth() / c_BossHealth * barWidth;
      Graphics::FillRectangle(m_Renderer, boss, Color::DarkGreen);
    }
  }
}

void Game::DrawTitle()
{
  Texture* titleTexture = Texture::TextureList["Title"];
  SDL_Rect titleRect = { c_HalfScreenWidth - titleTexture->GetWidth() / 2, c_HalfScreenHeight - titleTexture->GetHeight() / 2 - 100, titleTexture->GetWidth(), titleTexture->GetHeight() };
  SDL_RenderCopy(m_Renderer, titleTexture->GetTexture(0), nullptr, &titleRect);

  Graphics::DrawText(m_Renderer, m_Font25, "Press ENTER to Start", c_HalfScreenWidth, c_HalfScreenHeight + 75, Color::White);
  Graphics::DrawText(m_Renderer, m_Font20, (m_IsSinglePlayer ? "1-Player" : "2-Player"), c_HalfScreenWidth, c_HalfScreenHeight + 100, Color::White);

  Graphics::DrawText(m_Renderer, m_Font20, "Players", c_HalfScreenWidth - 100, c_HalfScreenHeight + 150, Color::White);
  Graphics::DrawText(m_Renderer, m_Font20, "(1)", c_HalfScreenWidth + 100, c_HalfScreenHeight + 150, Color::White);

  Graphics::DrawText(m_Renderer, m_Font20, "Controls", c_HalfScreenWidth - 100, c_HalfScreenHeight + 175, Color::White);
  Graphics::DrawText(m_Renderer, m_Font20, "(2)", c_HalfScreenWidth + 100, c_HalfScreenHeight + 175, Color::White);

  Graphics::DrawText(m_Renderer, m_Font20, "Credits", c_HalfScreenWidth - 100, c_HalfScreenHeight + 200, Color::White);
  Graphics::DrawText(m_Renderer, m_Font20, "(3)", c_HalfScreenWidth + 100, c_HalfScreenHeight + 200, Color::White);

  Graphics::DrawText(m_Renderer, m_Font20, "Debug", c_HalfScreenWidth - 100, c_HalfScreenHeight + 225, Color::White);
  Graphics::DrawText(m_Renderer, m_Font20, "(Tab)", c_HalfScreenWidth + 100, c_HalfScreenHeight + 225, Color::White);

  Graphics::DrawText(m_Renderer, m_Font20, "Exit", c_HalfScreenWidth - 100, c_HalfScreenHeight + 250, Color::White);
  Graphics::DrawText(m_Renderer, m_Font20, "(Esc)", c_HalfScreenWidth + 100, c_HalfScreenHeight + 250, Color::White);
}

void Game::DrawControls()
{
  Texture* keyTexture = Texture::TextureList["Keyboard"];
  SDL_Rect keyRect = { c_HalfScreenWidth - keyTexture->GetWidth() / 2, c_HalfScreenHeight - keyTexture->GetHeight() / 2, keyTexture->GetWidth(), keyTexture->GetHeight() };
  SDL_RenderCopy(m_Renderer, keyTexture->GetTexture(0), nullptr, &keyRect);

  Graphics::DrawText(m_Renderer, m_Font35, "CONTROLS", c_HalfScreenWidth, 40, Color::White);
  Graphics::DrawText(m_Renderer, m_Font16, "Press ENTER to Return to Main Menu", c_HalfScreenWidth, c_ScreenHeight - 40, Color::White);
}

void Game::DrawCredits()
{
  Graphics::DrawText(m_Renderer, m_Font35, "CREDITS", c_HalfScreenWidth, 40, Color::White);

  Graphics::DrawText(m_Renderer, m_Font14, "Programming", c_HalfScreenWidth, 150, Color::White);
  Graphics::DrawText(m_Renderer, m_Font25, "Jason Norris", c_HalfScreenWidth, 170, Color::White);

  Graphics::DrawText(m_Renderer, m_Font14, "Programming", c_HalfScreenWidth, 250, Color::White);
  Graphics::DrawText(m_Renderer, m_Font25, "Jason Norris", c_HalfScreenWidth, 270, Color::White);

  Graphics::DrawText(m_Renderer, m_Font14, "Programming", c_HalfScreenWidth, 350, Color::White);
  Graphics::DrawText(m_Renderer, m_Font25, "Jason Norris", c_HalfScreenWidth, 370, Color::White);

  Graphics::DrawText(m_Renderer, m_Font16, "Press ENTER to Return to Main Menu", c_HalfScreenWidth, c_ScreenHeight - 40, Color::White);
}

void Game::DrawPaused()
{
  SDL_Rect rect = { 0, 0, c_ScreenWidth, c_ScreenHeight };
  Graphics::FillRectangle(m_Renderer, rect, Color::BlackTransparent);
  Graphics::DrawText(m_Renderer, m_Font35, "PAUSED", c_HalfScreenWidth, c_HalfScreenHeight, Color::White);
}

void Game::DrawGameOver()
{
  SDL_Rect rect = { 0, 0, c_ScreenWidth, c_ScreenHeight };
  Graphics::FillRectangle(m_Renderer, rect, Color::RedTransparent);
  Graphics::DrawText(m_Renderer, m_Font35, "FAILURE", c_HalfScreenWidth, c_HalfScreenHeight, Color::Red);
  Graphics::DrawText(m_Renderer, m_Font14, "Press ENTER to Return to Main Menu", c_HalfScreenWidth, c_HalfScreenHeight + 50, Color::Red);
}

void Game::DrawVictory()
{
  SDL_Rect rect = { 0, 0, c_ScreenWidth, c_ScreenHeight };
  Graphics::FillRectangle(m_Renderer, rect, Color::GreenTransparent);
  Graphics::DrawText(m_Renderer, m_Font35, "SUCCESS", c_HalfScreenWidth, c_HalfScreenHeight, Color::Green);
  Graphics::DrawText(m_Renderer, m_Font14, "Press ENTER to Return to Main Menu", c_HalfScreenWidth, c_HalfScreenHeight + 50, Color::Green);
}

void Game::DrawDebug()
{
  std::stringstream ss;
  ss << "FPS: " << m_FramesPerSecond << "\nObjects: " << m_ObjectCount;
  Graphics::DrawText(m_Renderer, m_Font14, ss.str(), 10, 10, Color::White, false);
}
