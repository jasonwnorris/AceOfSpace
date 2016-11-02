// Graphics.cpp

// SDL Includes
#include <SDL_ttf.h>
// AOS Includes
#include "Graphics.hpp"

// draws text to screen, eats up a lot of CPU cycles
void Graphics::DrawText(SDL_Renderer* renderer, std::string text, int size, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center)
{
  SDL_Color color = {red, green, blue};
  TTF_Font* font = TTF_OpenFont("resources/framd.ttf", size);
  SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Rect rect = {x, y, surface->w, surface->h};
  if (center)
  {
    rect.x -= surface->w / 2;
    rect.y -= surface->h / 2;
  }

  SDL_RenderCopy(renderer, texture, nullptr, &rect);

  TTF_CloseFont(font);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void Graphics::FillAlphaRect(SDL_Renderer* renderer, SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
  SDL_RenderFillRect(renderer, &rect);
}
