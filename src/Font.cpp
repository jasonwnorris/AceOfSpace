// Font.cpp

// SDL Includes
#include <SDL.h>
// STL Includes
#include <algorithm>
// AOS Includes
#include "Font.hpp"

bool Glyph::operator==(const Glyph& p_Other)
{
  return this->Character == p_Other.Character && this->Index == p_Other.Index;
}

Font::Font()
{
  m_Texture = nullptr;
  m_IsLoaded = false;
}

Font::~Font()
{
  if (m_IsLoaded)
  {
    Unload();
  }
}

float Font::GetCharacterSpacing(Uint16 p_Character) const
{
  for (const auto& glyph : m_Glyphs)
  {
    if (glyph.Character == p_Character)
    {
      return static_cast<float>(glyph.Advance + glyph.MinX);
    }
  }

  return 0.0f;
}

float Font::GetLineSpacing() const
{
  return static_cast<float>(m_LineSkip);
}

SDL_Texture* Font::GetTexture() const
{
  return m_Texture;
}

SDL_Rect Font::GetCharacterBounds(Uint16 p_Character) const
{
  SDL_Rect rect = { 0, 0, 0, 0 };

  for (const auto& glyph : m_Glyphs)
  {
    if (glyph.Character == p_Character)
    {
      rect.x = glyph.VisualX;
      rect.y = glyph.VisualY;
      rect.w = glyph.VisualWidth;
      rect.h = glyph.VisualHeight;

      return rect;
    }
  }

  return rect;
}

void Font::MeasureString(const std::string& p_Text, int& p_Width, int& p_Height) const
{
  p_Width = 0;
  p_Height = m_Height;

  for (char character : p_Text)
  {
    SDL_Rect bounds = GetCharacterBounds(character);

    p_Width += bounds.w;
  }
}

bool Font::Load(SDL_Renderer* p_Renderer, const std::string& p_Filename, int p_Size, int p_Style, int p_Hinting, int p_Outline, bool p_UseKerning)
{
  // Open the font.
  TTF_Font* font = TTF_OpenFont(p_Filename.c_str(), p_Size);
  if (font == nullptr)
  {
    SDL_Log("Failed to load TTF file: %s", SDL_GetError());
    return false;
  }

  // Set options.
  TTF_SetFontStyle(font, p_Style);
  TTF_SetFontHinting(font, p_Hinting);
  TTF_SetFontOutline(font, p_Outline);
  TTF_SetFontKerning(font, p_UseKerning ? SDL_ENABLE : SDL_DISABLE);

  // Collect metrics.
  m_Height = TTF_FontHeight(font);
  m_Ascent = TTF_FontAscent(font);
  m_Descent = TTF_FontDescent(font);
  m_LineSkip = TTF_FontLineSkip(font);
  m_Faces = TTF_FontFaces(font);
  m_IsFixedWidth = TTF_FontFaceIsFixedWidth(font) > 0;
  char* faceFamilyName = TTF_FontFaceFamilyName(font);
  if (faceFamilyName != nullptr)
  {
    m_FaceFamilyName.assign(faceFamilyName);
  }
  char* faceStyleName = TTF_FontFaceStyleName(font);
  if (faceStyleName != nullptr)
  {
    m_FaceStyleName.assign(faceStyleName);
  }

  // Collect glyph metrics.
  const Uint16 maxGlyphs = 65535;
  for (Uint16 ch = 0; ch < maxGlyphs; ++ch)
  {
    int index = TTF_GlyphIsProvided(font, ch);
    if (index != 0)
    {
      Glyph glyph;
      glyph.Character = ch;
      glyph.Index = index;

      SDL_Color color = { 255, 255, 255 };
      SDL_Surface* surface = TTF_RenderGlyph_Blended(font, ch, color);
      if (surface == nullptr)
      {
        SDL_Log("Failed to render TTF surface for character '%c': %s", ch, SDL_GetError());
        continue;
      }

      glyph.Surface = surface;
      glyph.VisualWidth = glyph.Surface->w;
      glyph.VisualHeight = glyph.Surface->h;

      m_Glyphs.push_back(glyph);
    }
  }

  // Print metrics.
  SDL_Log("Loaded font: Height: %d, Ascent: %d, Descent: %d, Line Skip: %d, Faces: %ld, Fixed: %s, Family Name: %s, Style Name: %s, Glyphs: %d",
    m_Height, m_Ascent, m_Descent, m_LineSkip, m_Faces, m_IsFixedWidth ? "yes" : "no",
    m_FaceFamilyName.c_str(), m_FaceStyleName.c_str(),
    static_cast<int>(m_Glyphs.size()));

  // Close the font.
  TTF_CloseFont(font);

  // Sort glyphs by height.
  std::sort(m_Glyphs.begin(), m_Glyphs.end(), [](const Glyph& glyphA, const Glyph& glyphB) {
    return glyphA.VisualHeight > glyphB.VisualHeight;
  });

  // Pack glyphs into area.
  int offsetX = 0;
  int offsetY = 0;
  int sizeWidth = HeuristicWidth();
  int maxHeight = 0;
  for (auto& glyph : m_Glyphs)
  {
    if (offsetX + glyph.VisualWidth > sizeWidth)
    {
      offsetX = 0;
      offsetY += maxHeight;
      maxHeight = 0;
    }
    glyph.VisualX = offsetX;
    glyph.VisualY = offsetY;
    offsetX += glyph.VisualWidth;
    maxHeight = std::max(glyph.VisualHeight, maxHeight);
  }
  int sizeHeight = MakeValidTextureSize(offsetY + maxHeight);

  // Collapse glyphs into single surface.
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  Uint32 Rmask = 0xff000000;
  Uint32 Gmask = 0x00ff0000;
  Uint32 Bmask = 0x0000ff00;
  Uint32 Amask = 0x000000ff;
#else
  Uint32 Rmask = 0x000000ff;
  Uint32 Gmask = 0x0000ff00;
  Uint32 Bmask = 0x00ff0000;
  Uint32 Amask = 0xff000000;
#endif
  SDL_Surface* canvas = SDL_CreateRGBSurface(0, sizeWidth, sizeHeight, 32, Rmask, Gmask, Bmask, Amask);
  for (const auto& glyph : m_Glyphs)
  {
    SDL_Rect destination = {
      glyph.VisualX,
      glyph.VisualY,
      glyph.VisualWidth,
      glyph.VisualHeight
    };
    SDL_BlitSurface(glyph.Surface, nullptr, canvas, &destination);
  }

  // Create texture from surface.
  m_Texture = SDL_CreateTextureFromSurface(p_Renderer, canvas);
  SDL_SetTextureBlendMode(m_Texture, SDL_BLENDMODE_BLEND);

  // Clean up surfaces.
  for (auto& glyph : m_Glyphs)
  {
    SDL_FreeSurface(glyph.Surface);
  }
  SDL_FreeSurface(canvas);

  return true;
}

bool Font::Unload()
{
  SDL_DestroyTexture(m_Texture);

  m_IsLoaded = false;

  return true;
}

int Font::HeuristicWidth()
{
  int totalSize = 0;
  for (const auto& glyph : m_Glyphs)
  {
    totalSize += glyph.VisualWidth * glyph.VisualHeight;
  }

  return MakeValidTextureSize(static_cast<int>(sqrt(totalSize)), true);
}

int Font::MakeValidTextureSize(int p_Value, bool p_IsPOT)
{
  const int blockSize = 4;

  if (p_IsPOT)
  {
    int value = blockSize;

    while (value < p_Value)
    {
      value <<= 1;
    }

    return value;
  }

  return p_Value;
}
