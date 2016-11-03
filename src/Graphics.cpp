// Graphics.cpp

// AOS Includes
#include "Graphics.hpp"

void Graphics::DrawText(SDL_Renderer* renderer, const Font& font, const std::string& text, int x, int y, SDL_Color color, bool center)
{
  int width = 0;
  int height = 0;
  if (center)
  {
    font.MeasureString(text, width, height);
  }

  SDL_Texture* texture = font.GetTexture();
  SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
  SDL_SetTextureAlphaMod(texture, color.a);

  int offset = 0;
  for (char character : text)
  {
    SDL_Rect source = font.GetCharacterBounds(character);
    SDL_Rect destination = { x + offset - width / 2, y - height / 2, source.w, source.h };

    SDL_RenderCopy(renderer, texture, &source, &destination);

    offset += source.w;
  }
}

void Graphics::FillAlphaRect(SDL_Renderer* renderer, SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderFillRect(renderer, &rect);
}
