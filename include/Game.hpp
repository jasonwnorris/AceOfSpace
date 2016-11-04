// Game.hpp

#ifndef __GAME_HPP__
#define __GAME_HPP__

// SDL Includes
#include <SDL.h>
// AOS Includes
#include "Level.hpp"
#include "Timer.hpp"
#include "Font.hpp"
#include "Starfield.hpp"

enum GameState
{
  STATE_MENU,
  STATE_CONTROLS,
  STATE_CREDITS,
  STATE_PLAYING,
  STATE_PAUSED,
  STATE_GAMEOVER,
  STATE_VICTORY
};

class Game
{
  public:
    Game();
    ~Game();

    bool OnExecute();

    bool OnStart();
    void OnEnd();

    void OnThink();
    void OnUpdate();
    void OnRender();

  private:
    void DrawHUD();
    void DrawTitle();
    void DrawControls();
    void DrawCredits();
    void DrawPaused();
    void DrawGameOver();
    void DrawVictory();
    void DrawDebug();

    static const SDL_Color c_White;
    static const SDL_Color c_Green;
    static const SDL_Color c_Red;

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Event m_Event;
    bool m_IsDone;
    float m_Interval;
    float m_ElapsedTime;
    int m_FrameCount;
    int m_FramesPerSecond;
    int m_ObjectCount;
    int m_State;
    bool m_IsSinglePlayer;
    bool m_IsDebugShown;
    Timer m_Timer;
    Level m_Level;
    Font m_Font10;
    Font m_Font14;
    Font m_Font16;
    Font m_Font20;
    Font m_Font25;
    Font m_Font35;
    Starfield m_Starfield;
};

#endif
