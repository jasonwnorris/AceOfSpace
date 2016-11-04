// Font.hpp

#ifndef __FONT_HPP__
#define __FONT_HPP__

// SDL Includes
#include <SDL_ttf.h>
// STL Includes
#include <string>
#include <vector>
// AOS Includes
#include "Glyph.hpp"
#include "Vector2f.hpp"

class Font
{
  public:
    Font();
    ~Font();

    float GetCharacterSpacing(Uint16 p_Character) const;
    int GetHeight() const;
    int GetLineSkip() const;

    SDL_Texture* GetTexture() const;
    SDL_Rect GetCharacterBounds(Uint16 p_Character) const;

    void MeasureString(const std::string& p_Text, int& p_Width, int& p_Height) const;

    bool Load(SDL_Renderer* p_Renderer, const std::string& p_Filename, int p_Size, int p_Style = TTF_STYLE_NORMAL, int p_Hinting = TTF_HINTING_NORMAL, int p_Outline = 0, bool p_UseKerning = true);
    bool Unload();

  private:
    int HeuristicWidth();
    int MakeValidTextureSize(int p_Value, bool p_IsPOT = true);

    SDL_Texture* m_Texture;
    bool m_IsLoaded;
    int m_Height;
    int m_Ascent;
    int m_Descent;
    int m_LineSkip;
    long m_Faces;
    bool m_IsFixedWidth;
    std::string m_FaceFamilyName;
    std::string m_FaceStyleName;
    std::vector<Glyph> m_Glyphs;
};

#endif
