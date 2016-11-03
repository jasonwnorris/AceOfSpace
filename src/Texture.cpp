// Texture.cpp

// STL Includes
#include <algorithm>
// AOS Includes
#include "Texture.hpp"

std::map<std::string, Texture*> Texture::TextureList;

Texture::Texture(SDL_Renderer* renderer, const std::string& filename, int tilesX, int tilesY, int frameCount, float frameRate, bool collidable)
{
  m_Textures[0] = LoadImage(renderer, filename);

  SDL_QueryTexture(m_Textures[0], &m_Format, nullptr, &m_Width, &m_Height);

  if (collidable)
  {
    MakeDamageTexture(renderer, filename);
  }

  m_TilesX = tilesX;
  m_TilesY = tilesY;
  m_TileWidth = m_Width / tilesX;
  m_TileHeight = m_Height / tilesY;
  m_FrameCount = frameCount;
  m_FrameInterval = 1.0f / frameRate;
  m_IsCollidable = collidable;
}

Texture::~Texture()
{
  SDL_DestroyTexture(m_Textures[0]);

  if (m_IsCollidable)
  {
    delete[] m_IsPixelSolid;
    SDL_DestroyTexture(m_Textures[1]);
  }
}

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

    Texture* m_Texture = new Texture(renderer, filename, tilesX, tilesY, frameCount, frameRate, (collidable == "yes"));
    TextureList[keyname] = m_Texture;
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

SDL_Texture* Texture::LoadImage(SDL_Renderer* renderer, const std::string& filename)
{
  std::string filepath = "resources/" + filename;
  SDL_Surface* surface = IMG_Load(filepath.c_str());
  SDL_Texture* m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  return m_Texture;
}

void Texture::MakeDamageTexture(SDL_Renderer* renderer, const std::string& filename)
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

  m_IsPixelSolid = new bool[surface->w * surface->h];

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
      m_IsPixelSolid[index] = (alpha == 255);
    }
  }

  if (SDL_MUSTLOCK(surface))
  {
    SDL_UnlockSurface(surface);
  }

  m_Textures[1] = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}
