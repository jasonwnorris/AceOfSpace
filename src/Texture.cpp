// Texture.cpp //
#include "Texture.hpp"

#include <algorithm>

std::map<std::string, Texture*> Texture::TextureList;

Texture::Texture(SDL_Renderer* renderer, std::string filename, int tilesX, int tilesY, int frameCount, float frameRate, bool collidable)
{
  textures[0] = LoadImage(renderer, filename);

  SDL_QueryTexture(textures[0], &this->format, nullptr, &this->width, &this->height);

  if (collidable)
  {
    MakeDamageTexture(renderer, filename);
  }

  this->tilesX = tilesX;
  this->tilesY = tilesY;
  this->tileWidth = this->width / tilesX;
  this->tileHeight = this->height / tilesY;
  this->frameCount = frameCount;
  this->frameInterval = 1 / frameRate;
  this->collidable = collidable;
}

Texture::~Texture()
{
  SDL_DestroyTexture(textures[0]);

  if (collidable)
  {
    delete[] solidity;
    SDL_DestroyTexture(textures[1]);
  }
}

// load in texture files from text document
void Texture::LoadTextures(SDL_Renderer* renderer)
{
  std::ifstream file;

  file.open("resources/textures.txt");

  std::string keyname = "";
  std::string filename = "";
  int tilesX = 0;
  int tilesY = 0;
  int frameCount = 0;
  float frameRate = 0.0f;
  std::string collidable = "";

  getline(file, keyname);

  while (!file.eof())
  {
    file >> keyname;
    file >> filename;
    file >> tilesX;
    file >> tilesY;
    file >> frameCount;
    file >> frameRate;
    file >> collidable;

    Texture* texture = new Texture(renderer, filename, tilesX, tilesY, frameCount, frameRate, (collidable == "yes"));
    TextureList[keyname] = texture;
    SDL_Log("Loaded texture: %s", keyname.c_str());
  }

  file.close();
}

void Texture::UnloadTextures()
{
  for (std::map<std::string, Texture*>::iterator Iter = TextureList.begin(); Iter != TextureList.end(); ++Iter)
  {
    SDL_Log("Deleting texture: %s", (*Iter).first.c_str());
    delete (*Iter).second;
  }

  TextureList.clear();
}

SDL_Texture* Texture::LoadImage(SDL_Renderer* renderer, std::string filename)
{
  std::string filepath = "resources/" + filename;
  SDL_Surface* surface = IMG_Load(filepath.c_str());
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  return texture;
}

void Texture::MakeDamageTexture(SDL_Renderer* renderer, std::string filename)
{
  std::string filepath = "resources/" + filename;
  SDL_Surface* surface = IMG_Load(filepath.c_str());

  if (SDL_MUSTLOCK(surface))
  {
    SDL_LockSurface(surface);
  }

  Uint32* pixels = (Uint32*)surface->pixels;
  Uint8 red;
  Uint8 green;
  Uint8 blue;
  Uint8 alpha;

  solidity = new bool[width * height];

  for (int x = 0; x < surface->w; ++x)
  {
    for (int y = 0; y < surface->h; ++y)
    {
      int index = x + y * surface->w;
      SDL_GetRGBA(pixels[index], surface->format, &red, &green, &blue, &alpha);
      red = std::min(red + 100, 255);
      green = std::min(green + 100, 255);
      blue = std::min(blue + 100, 255);
      pixels[index] = SDL_MapRGBA(surface->format, red, green, blue, alpha);
      solidity[index] = (alpha == 255);
    }
  }

  if (SDL_MUSTLOCK(surface))
  {
    SDL_UnlockSurface(surface);
  }

  textures[1] = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}
