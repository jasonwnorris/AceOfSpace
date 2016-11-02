// Graphics.hpp

#ifndef __GRAPHICS_HPP__
#define __GRAPHICS_HPP__

// SDL Includes
#include <SDL.h>
// STL Includes
#include <string>
// AOS Includes
#include "Font.hpp"

class Graphics
{
  public:
    static void DrawText(SDL_Renderer* renderer, const Font& font, const std::string& text, int x, int y, SDL_Color color, bool center = true);
    static void FillAlphaRect(SDL_Renderer* renderer, SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
};

#endif
