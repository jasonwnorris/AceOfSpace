// Graphics.cpp

// AOS Includes
#include "Graphics.hpp"

void Graphics::DrawText(SDL_Renderer* p_Renderer, const Font& p_Font, const std::string& p_Text, int p_X, int p_Y, SDL_Color p_Color, bool p_IsCentered)
{
  int halfWidth = 0;
  int halfHeight = 0;
  if (p_IsCentered)
  {
    int width = 0;
    int height = 0;
    p_Font.MeasureString(p_Text, width, height);
    halfWidth = width / 2;
    halfHeight = height / 2;
  }

  SDL_Texture* texture = p_Font.GetTexture();
  SDL_SetTextureColorMod(texture, p_Color.r, p_Color.g, p_Color.b);
  SDL_SetTextureAlphaMod(texture, p_Color.a);

  int offsetX = 0;
  int offsetY = 0;
  for (char character : p_Text)
  {
    SDL_Rect source = p_Font.GetCharacterBounds(character);
    SDL_Rect destination = { p_X + offsetX - halfWidth, p_Y + offsetY - halfHeight, source.w, source.h };

    offsetX += source.w;
    if (character == '\n' || character == '\r')
    {
      offsetX = 0;
      offsetY += p_Font.GetHeight();
    }

    SDL_RenderCopy(p_Renderer, texture, &source, &destination);
  }
}

void Graphics::FillAlphaRect(SDL_Renderer* p_Renderer, SDL_Rect& p_Rect, Uint8 p_Red, Uint8 p_Green, Uint8 p_Blue, Uint8 p_Alpha)
{
  SDL_SetRenderDrawColor(p_Renderer, p_Red, p_Green, p_Blue, p_Alpha);
  SDL_RenderFillRect(p_Renderer, &p_Rect);
}
