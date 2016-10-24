#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>
using namespace std;

class Graphics
{
  public:
    Graphics();

    static void DrawText(SDL_Surface* screen, string text, int size, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center = true);
    static void FillAlphaRect(SDL_Surface* screen, SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
};

#endif
