// Texture.cpp //
#include "Texture.hpp"

#define COLOR_OFFSET  100

std::map<std::string, Texture*> Texture::TextureList;

Texture::Texture(SDL_Renderer* renderer, std::string filename, int tilesX, int tilesY, int frameCount, float frameRate, bool collidable)
{
  textures[0] = LoadImage(renderer, filename);

  SDL_QueryTexture(textures[0], &this->format, nullptr, &this->width, &this->height);

  if (collidable)
  {
    textures[1] = MakeDamageTexture(renderer);
  }
  else
  {
    textures[1] = nullptr;
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

SDL_Texture* Texture::MakeDamageTexture(SDL_Renderer* renderer)
{
  SDL_Rect rect = {0, 0, width, height};
  Uint32* pixels = new Uint32[width * height];
  int pitch = -1;

  SDL_SetRenderTarget(renderer, textures[0]);
  SDL_RenderReadPixels(renderer, &rect, format, pixels, pitch);
  SDL_SetRenderTarget(renderer, nullptr);

  SDL_PixelFormat* pixelFormat = SDL_AllocFormat(format);

  for (int i = 0; i < width * height; ++i)
  {
    Uint8 red, green, blue, alpha;
    SDL_GetRGBA(pixels[i], pixelFormat, &red, &green, &blue, &alpha);
    pixels[i] = SDL_MapRGBA(pixelFormat, 255, 255, 255, alpha);
  }

  SDL_FreeFormat(pixelFormat);

  SDL_Texture* texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STATIC, width, height);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  SDL_UpdateTexture(texture, &rect, pixels, pitch);

  delete [] pixels;

  return texture;
}
