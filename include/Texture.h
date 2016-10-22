// Texture.h //
#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <fstream>
#include <string>
#include <map>
using namespace std;

#include "Config.h"

class Texture
{
  public:
    Texture(string filename, int tilesX, int tilesY, int frameCount, float frameRate, bool collidable);
    ~Texture();
    
    static map<string,Texture*> TextureList;
    
    static void LoadTextures();
    static void UnloadTextures();
    
    static SDL_Surface* LoadImage(string filename);
    static void DrawText(SDL_Surface* screen, string text, int size, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center = true);
    static void FillAlphaRect(SDL_Surface* screen, SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
    
    SDL_Surface* textures[2];

        int tilesX;
        int tilesY;
        int tileWidth;
        int tileHeight;
        int frameCount;
        float frameInterval;
        bool collidable;
    
  private:
    SDL_Surface* MakeDamageTexture(string filename);
};

#endif
