// Texture.hpp

#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <fstream>
#include <string>
#include <map>

#include "Config.hpp"

class Texture
{
  public:
    Texture(SDL_Renderer* renderer, std::string filename, int tilesX, int tilesY, int frameCount, float frameRate, bool collidable);
    ~Texture();

    static std::map<std::string, Texture*> TextureList;

    static void LoadTextures(SDL_Renderer* renderer);
    static void UnloadTextures();
    static SDL_Texture* LoadImage(SDL_Renderer* renderer, std::string filename);

    SDL_Texture* textures[2];

    int width;
    int height;
    Uint32 format;
    int tilesX;
    int tilesY;
    int tileWidth;
    int tileHeight;
    int frameCount;
    float frameInterval;
    bool collidable;
    bool* solidity;

  private:
    SDL_Texture* MakeDamageTexture(SDL_Renderer* renderer);
};

#endif
