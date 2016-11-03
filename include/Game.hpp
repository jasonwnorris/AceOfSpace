// Game.hpp

#ifndef __GAME_HPP__
#define __GAME_HPP__

// SDL Includes
#include <SDL.h>
// AOS Includes
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

    void OnExecute();

    void OnStart();
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

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    bool done;
    float interval;
    float elapsedTime;
    int frameCount;
    int framesPerSecond;
    int objectCount;
    int gamestate;
    bool singlePlayer;
    bool showDebug;

    Timer timer;
    Font font10;
    Font font14;
    Font font16;
    Font font20;
    Font font25;
    Font font35;

    Starfield starfield;
};

#endif
