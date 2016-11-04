// Graphics.cpp

// AOS Includes
#include "Graphics.hpp"

void Graphics::DrawText(SDL_Renderer* p_Renderer, const Font& p_Font, const std::string& p_Text, int p_X, int p_Y, SDL_Color p_Color, bool p_IsCentered)
{
  int width = 0;
  int height = 0;
  if (p_IsCentered)
  {
    p_Font.MeasureString(p_Text, width, height);
  }

  SDL_Texture* texture = p_Font.GetTexture();
  SDL_SetTextureColorMod(texture, p_Color.r, p_Color.g, p_Color.b);
  SDL_SetTextureAlphaMod(texture, p_Color.a);

  int offset = 0;
  for (char character : p_Text)
  {
    SDL_Rect source = p_Font.GetCharacterBounds(character);
    SDL_Rect destination = { p_X + offset - width / 2, p_Y - height / 2, source.w, source.h };

    SDL_RenderCopy(p_Renderer, texture, &source, &destination);

    offset += source.w;
  }
}

void Graphics::FillAlphaRect(SDL_Renderer* p_Renderer, SDL_Rect& p_Rect, Uint8 p_Red, Uint8 p_Green, Uint8 p_Blue, Uint8 p_Alpha)
{
  SDL_SetRenderDrawColor(p_Renderer, p_Red, p_Green, p_Blue, p_Alpha);
  SDL_SetRenderDrawBlendMode(p_Renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderFillRect(p_Renderer, &p_Rect);
}
