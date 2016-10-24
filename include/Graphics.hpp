// Graphics.hpp

#ifndef __GRAPHICS_HPP__
#define __GRAPHICS_HPP__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>

class Graphics
{
  public:
    Graphics();

    static void DrawText(SDL_Surface* screen, std::string text, int size, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center = true);
    static void FillAlphaRect(SDL_Surface* screen, SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
};

#endif
