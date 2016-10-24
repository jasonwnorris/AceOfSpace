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
    textures[1] = MakeDamageTexture(renderer, filename);
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
    printf("Loaded texture: %s\n", keyname.c_str());
  }

  file.close();
}

void Texture::UnloadTextures()
{
  for (std::map<std::string, Texture*>::iterator Iter = TextureList.begin(); Iter != TextureList.end(); ++Iter)
  {
    printf("Deleting texture: %s\n", (*Iter).first.c_str());
    delete (*Iter).second;
  }

  TextureList.clear();
}

// simple image loading function
SDL_Texture* Texture::LoadImage(SDL_Renderer* renderer, std::string filename)
{
  std::string filepath = "resources/" + filename;
  SDL_Surface* surface = IMG_Load(filepath.c_str());
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  return texture;
}

// draws text to screen, eats up a lot of CPU cycles
void Texture::DrawText(SDL_Renderer* renderer, std::string text, int size, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center)
{
  SDL_Color color = {red, green, blue};
  TTF_Font* font = TTF_OpenFont("resources/framd.ttf", size);
  SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Rect rect = {x, y, surface->w, surface->h};
  if (center)
  {
    rect.x -= surface->w / 2;
    rect.y -= surface->h / 2;
  }

  SDL_RenderCopy(renderer, texture, nullptr, &rect);

  TTF_CloseFont(font);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void Texture::FillAlphaRect(SDL_Renderer* renderer, SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
  SDL_RenderFillRect(renderer, &rect);
}

// TEMP: Just loads same texture.
SDL_Texture* Texture::MakeDamageTexture(SDL_Renderer* renderer, std::string filename)
{
  return LoadImage(renderer, filename);
}
