// Color.hpp

#ifndef __COLOR_HPP__
#define __COLOR_HPP__

// SDL Includes
#include <SDL.h>

struct Color
{
  static const SDL_Color White;
  static const SDL_Color Green;
  static const SDL_Color Red;

  static const SDL_Color DarkGray;
  static const SDL_Color DarkRed;
  static const SDL_Color DarkGreen;
  static const SDL_Color DarkBlue;

  static const SDL_Color BlackTransparent;
  static const SDL_Color GreenTransparent;
  static const SDL_Color RedTransparent;
};

#endif
