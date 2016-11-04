// Texture.hpp

#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

// SDL Includes
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
// STL Includes
#include <fstream>
#include <string>
#include <map>
// AOS Includes
#include "Config.hpp"

class Texture
{
  public:
    Texture(SDL_Renderer* p_Renderer, const std::string& p_Filename, int p_TilesX, int p_TilesY, int p_FrameCount, float p_FrameRate, bool p_IsCollidable);
    ~Texture();

    SDL_Texture* GetTexture(int p_Index) const;
    int GetWidth() const;
    int GetHeight() const;
    Uint32 GetFormat() const;
    int GetTilesX() const;
    int GetTilesY() const;
    int GetTileWidth() const;
    int GetTileHeight() const;
    int GetFrameCount() const;
    float GetFrameInterval() const;
    bool IsCollidable() const;
    bool IsPixelSolid(int p_X, int p_Y) const;

    static std::map<std::string, Texture*> TextureList;

    static bool LoadTextures(SDL_Renderer* p_Renderer);
    static void UnloadTextures();
    static SDL_Texture* LoadImage(SDL_Renderer* p_Renderer, const std::string& p_Filename);

  private:
    void MakeDamageTexture(SDL_Renderer* p_Renderer, const std::string& p_Filename);

    SDL_Texture* m_Textures[2];
    int m_Width;
    int m_Height;
    Uint32 m_Format;
    int m_TilesX;
    int m_TilesY;
    int m_TileWidth;
    int m_TileHeight;
    int m_FrameCount;
    float m_FrameInterval;
    bool m_IsCollidable;
    bool* m_IsPixelSolid;
};

#endif
