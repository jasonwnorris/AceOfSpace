/// ACE OF SPACE
/// Copyright Jason Norris 2009.

// main.cpp
#include "Game.hpp"

int main(int p_ArgCount, char** p_ArgVars)
{
  Game game;
  if (!game.OnExecute())
  {
    return -1;
  }

  return 0;
}
