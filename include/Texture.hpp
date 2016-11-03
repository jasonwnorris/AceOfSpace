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
    Texture(SDL_Renderer* renderer, const std::string& filename, int tilesX, int tilesY, int frameCount, float frameRate, bool collidable);
    ~Texture();

    static std::map<std::string, Texture*> TextureList;

    static void LoadTextures(SDL_Renderer* renderer);
    static void UnloadTextures();
    static SDL_Texture* LoadImage(SDL_Renderer* renderer, const std::string& filename);

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

  private:
    void MakeDamageTexture(SDL_Renderer* renderer, const std::string& filename);
};

#endif
