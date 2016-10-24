// Texture.h //
#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <fstream>
#include <string>
#include <map>
using namespace std;

#include "Config.hpp"

class Texture
{
  public:
    Texture(SDL_Renderer* renderer, string filename, int tilesX, int tilesY, int frameCount, float frameRate, bool collidable);
    ~Texture();

    static map<string,Texture*> TextureList;

    static void LoadTextures(SDL_Renderer* renderer);
    static void UnloadTextures();

    static SDL_Texture* LoadImage(SDL_Renderer* renderer, string filename);
    static void DrawText(SDL_Renderer* renderer, string text, int size, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center = true);
    static void FillAlphaRect(SDL_Renderer* renderer, SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

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

  private:
    SDL_Texture* MakeDamageTexture(SDL_Renderer* renderer, string filename);
};

#endif
