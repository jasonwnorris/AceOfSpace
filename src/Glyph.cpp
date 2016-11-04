// Glyph.cpp

// AOS Includes
#include "Glyph.hpp"

bool Glyph::operator==(const Glyph& p_Other)
{
  return this->Character == p_Other.Character && this->Index == p_Other.Index;
}
