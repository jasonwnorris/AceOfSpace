// Glyph.hpp

#ifndef __GLYPH_HPP__
#define __GLYPH_HPP__

// SDL Includes
#include <SDL.h>

struct Glyph
{
  Uint16 Character;
  int Index;
  int MinX;
  int MaxX;
  int MinY;
  int MaxY;
  int Advance;
  int SpacialWidth;
  int SpacialHeight;
  int VisualX;
  int VisualY;
  int VisualWidth;
  int VisualHeight;
  SDL_Surface* Surface;

  bool operator==(const Glyph& p_Other);
};

#endif
