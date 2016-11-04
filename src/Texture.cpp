// Texture.cpp

// SDL Includes
#include <SDL_image.h>
// STL Includes
#include <algorithm>
#include <fstream>
// AOS Includes
#include "Texture.hpp"

std::map<std::string, Texture*> Texture::TextureList;

Texture::Texture(SDL_Renderer* p_Renderer, const std::string& p_Filename, int p_TilesX, int p_TilesY, int p_FrameCount, float p_FrameRate, bool p_IsCollidable)
{
  m_IsCollidable = p_IsCollidable;

  MakeTextures(p_Renderer, c_ResourcesPath + p_Filename);

  m_TilesX = p_TilesX;
  m_TilesY = p_TilesY;
  m_TileWidth = m_Width / p_TilesX;
  m_TileHeight = m_Height / p_TilesY;
  m_FrameCount = p_FrameCount;
  m_FrameInterval = 1.0f / p_FrameRate;
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

SDL_Texture* Texture::GetTexture(int p_Index) const
{
  return m_Textures[p_Index];
}

int Texture::GetWidth() const
{
  return m_Width;
}

int Texture::GetHeight() const
{
  return m_Height;
}

Uint32 Texture::GetFormat() const
{
  return m_Format;
}

int Texture::GetTilesX() const
{
  return m_TilesX;
}

int Texture::GetTilesY() const
{
  return m_TilesY;
}

int Texture::GetTileWidth() const
{
  return m_TileWidth;
}

int Texture::GetTileHeight() const
{
  return m_TileHeight;
}

int Texture::GetFrameCount() const
{
  return m_FrameCount;
}

float Texture::GetFrameInterval() const
{
  return m_FrameInterval;
}

bool Texture::IsCollidable() const
{
  return m_IsCollidable;
}

bool Texture::IsPixelSolid(int p_X, int p_Y) const
{
  if (p_X < 0 || p_X >= m_Width || p_Y < 0 || p_Y >= m_Height)
  {
    return false;
  }

  return m_IsPixelSolid[p_X + p_Y * m_Width];
}

bool Texture::LoadTextures(SDL_Renderer* p_Renderer)
{
  std::ifstream file(c_TexturesFilename, std::ios_base::in);
  if (!file.is_open())
  {
    SDL_Log("Failed to open file: %s", c_TexturesFilename.c_str());
    return false;
  }

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
    file >> keyname >> filename >> tilesX >> tilesY >> frameCount >> frameRate >> collidable;

    Texture* texture = new Texture(p_Renderer, filename, tilesX, tilesY, frameCount, frameRate, (collidable == "yes"));
    if (texture != nullptr)
    {
      SDL_Log("Loaded texture: %s", keyname.c_str());
      TextureList[keyname] = texture;
    }
    else
    {
      SDL_Log("Failed to load texture: %s", keyname.c_str());
      return false;
    }

  }

  file.close();

  return true;
}

void Texture::UnloadTextures()
{
  for (auto& pair : TextureList)
  {
    SDL_Log("Unloading texture: %s", pair.first.c_str());
    delete pair.second;
  }

  TextureList.clear();
}

void Texture::MakeTextures(SDL_Renderer* p_Renderer, const std::string& p_Filename)
{
  SDL_Surface* surface = IMG_Load(p_Filename.c_str());

  MakeStandardTexture(p_Renderer, surface);
  if (m_IsCollidable)
  {
    MakeDamageTexture(p_Renderer, surface);
  }

  SDL_FreeSurface(surface);
}

void Texture::MakeStandardTexture(SDL_Renderer* p_Renderer, SDL_Surface* p_Surface)
{
  m_Textures[0] = SDL_CreateTextureFromSurface(p_Renderer, p_Surface);

  SDL_QueryTexture(m_Textures[0], &m_Format, nullptr, &m_Width, &m_Height);
}

void Texture::MakeDamageTexture(SDL_Renderer* p_Renderer, SDL_Surface* p_Surface)
{
  if (SDL_MUSTLOCK(p_Surface))
  {
    SDL_LockSurface(p_Surface);
  }

  Uint32* pixels = (Uint32*)p_Surface->pixels;
  Uint8 red;
  Uint8 green;
  Uint8 blue;
  Uint8 alpha;

  m_IsPixelSolid = new bool[p_Surface->w * p_Surface->h];

  for (int x = 0; x < p_Surface->w; ++x)
  {
    for (int y = 0; y < p_Surface->h; ++y)
    {
      int index = x + y * p_Surface->w;
      SDL_GetRGBA(pixels[index], p_Surface->format, &red, &green, &blue, &alpha);
      red = std::min(red + 100, 255);
      green = std::min(green + 100, 255);
      blue = std::min(blue + 100, 255);
      pixels[index] = SDL_MapRGBA(p_Surface->format, red, green, blue, alpha);
      m_IsPixelSolid[index] = (alpha == 255);
    }
  }

  if (SDL_MUSTLOCK(p_Surface))
  {
    SDL_UnlockSurface(p_Surface);
  }

  m_Textures[1] = SDL_CreateTextureFromSurface(p_Renderer, p_Surface);
}
