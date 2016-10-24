// Game.h //
#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "Timer.hpp"
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

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    bool done;
    int frame;
    int gamestate;
    bool singlePlayer;
    bool showDebug;

    Timer timer;

    Starfield starfield;
};

#endif
