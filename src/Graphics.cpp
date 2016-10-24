#include "Graphics.hpp"

Graphics::Graphics()
{
}

void Graphics::DrawText(SDL_Surface* screen, std::string text, int size, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center)
{
  SDL_Color color = {red, green, blue};
  TTF_Font* font = TTF_OpenFont("resources/framd.ttf", size);
  SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
  SDL_Rect rect = {x, y};
  if (center)
  {
    rect.x -= surface->w / 2;
    rect.y -= surface->h / 2;
  }

  SDL_BlitSurface(surface, nullptr, screen, &rect);

  TTF_CloseFont(font);
  SDL_FreeSurface(surface);
}

void Graphics::FillAlphaRect(SDL_Surface* screen, SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
  #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 Rmask = 0xFF000000;
    Uint32 Gmask = 0x00FF0000;
    Uint32 Bmask = 0x0000FF00;
    Uint32 Amask = 0x000000FF;
  #else
    Uint32 Rmask = 0x000000FF;
    Uint32 Gmask = 0x0000FF00;
    Uint32 Bmask = 0x00FF0000;
    Uint32 Amask = 0xFF000000;
  #endif

  SDL_Surface* surfaceRect = SDL_CreateRGBSurface(SDL_SWSURFACE, rect.w, rect.h, screen->format->BitsPerPixel, Rmask, Gmask, Bmask, Amask);

  Uint32 color = SDL_MapRGBA(surfaceRect->format, red, green, blue, alpha);
  Uint32* pixels = (Uint32*)surfaceRect->pixels;

  for (int x = 0; x < surfaceRect->w; x++)
  {
    for (int y = 0; y < surfaceRect->h; y++)
    {
      pixels[(y * surfaceRect->w) + x] = color;
    }
  }

  SDL_BlitSurface(surfaceRect, nullptr, screen, &rect);

  SDL_FreeSurface(surfaceRect);
}
