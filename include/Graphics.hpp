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
    static void DrawText(SDL_Renderer* p_Renderer, const Font& p_Font, const std::string& p_Text, int p_X, int p_Y, SDL_Color p_Color, bool p_IsCentered = true);
    static void FillAlphaRect(SDL_Renderer* p_Renderer, SDL_Rect& p_Rect, Uint8 p_Red, Uint8 p_Green, Uint8 p_Blue, Uint8 p_Alpha);
};

#endif
