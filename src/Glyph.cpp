// Glyph.cpp

// AOS Includes
#include "Glyph.hpp"

bool Glyph::operator==(const Glyph& p_Other)
{
  return Character == p_Other.Character && Index == p_Other.Index;
}
