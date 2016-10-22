// Texture.cpp //
#include "Texture.hpp"

#define COLOR_OFFSET  100

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 Rmask = 0xFF000000;
    Uint32 Gmask = 0x00FF0000;
    Uint32 Bmask = 0x0000FF00;
    Uint32 Amask = 0x000000FF;
#else
    Uint32 Rmask = 0x000000FF;
    Uint32 Gmask = 0x0000FF00;
    Uint32 Bmask = 0x00FF0000;
    Uint32 Amask = 0xFF000000;
#endif

map<string,Texture*> Texture::TextureList;

Texture::Texture(string filename, int tilesX, int tilesY, int frameCount, float frameRate, bool collidable)
{
  textures[0] = LoadImage(filename);
      
  int width = textures[0]->w;
  int height = textures[0]->h;

  if(collidable)
    textures[1] = MakeDamageTexture(filename);
  else
      textures[1] = NULL;
  
  this->tilesX = tilesX;
    this->tilesY = tilesY;
    this->tileWidth = width / tilesX;
    this->tileHeight = height / tilesY;
    this->frameCount = frameCount;
    this->frameInterval = 1 / frameRate;
    this->collidable = collidable;
}

Texture::~Texture()
{
  SDL_FreeSurface(textures[0]);

  if(collidable)
    SDL_FreeSurface(textures[1]);
}

// load in texture files from text document
void Texture::LoadTextures()
{
  ifstream file;

    file.open("resources/textures.txt");

    string keyname = "";
    string filename = "";
  int tilesX = 0;
  int tilesY = 0;
  int frameCount = 0;
  float frameRate = 0.0f;
  string collidable = "";
  
  getline(file, keyname);

  while(!file.eof())
    {
    file >> keyname;
    file >> filename;
    file >> tilesX;
    file >> tilesY;
    file >> frameCount;
    file >> frameRate;
    file >> collidable;
    
    Texture* texture = new Texture(filename, tilesX, tilesY, frameCount, frameRate, (collidable == "yes"));
    TextureList[keyname] = texture;
    printf("Loaded texture: %s\n", keyname.c_str());
  }

    file.close();
}

void Texture::UnloadTextures()
{
   for(map<string,Texture*>::iterator Iter = TextureList.begin(); Iter != TextureList.end(); ++Iter)
   {
      printf("Deleting texture: %s\n", (*Iter).first.c_str());
      delete (*Iter).second;
   }

   TextureList.clear();
}

// simple image loading function
SDL_Surface* Texture::LoadImage(string filename)
{
  string filepath = "resources/" + filename;
  SDL_Surface* tempSurface = IMG_Load(filepath.c_str());
    SDL_Surface* formatSurface = SDL_DisplayFormatAlpha(tempSurface);
    SDL_FreeSurface(tempSurface);
    
    return formatSurface;
}

// draws text to screen, eats up a lot of CPU cycles
void Texture::DrawText(SDL_Surface* screen, string text, int size, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center)
{
  SDL_Color color = {red, green, blue};
  TTF_Font* font = TTF_OpenFont("resources/framd.ttf", size);
  SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
  SDL_Rect rect = {x, y};
  if(center)
  {
    rect.x -= surface->w / 2;
    rect.y -= surface->h / 2;
  }

  SDL_BlitSurface(surface, NULL, screen, &rect);

  TTF_CloseFont(font);
    SDL_FreeSurface(surface);
}

// SDL_FillRect wasn't cutting it for me
// creates an SDL_Surface entirely made of one color with transparency
// also chews on CPU cycles
void Texture::FillAlphaRect(SDL_Surface* screen, SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    SDL_Surface* surfaceRect = SDL_CreateRGBSurface(SDL_SWSURFACE, rect.w, rect.h, screen->format->BitsPerPixel, Rmask, Gmask, Bmask, Amask);

  Uint32 color = SDL_MapRGBA(surfaceRect->format, red, green, blue, alpha);
    Uint32* pixels = (Uint32*)surfaceRect->pixels;

    for(int x = 0; x < surfaceRect->w; ++x)
      for(int y = 0; y < surfaceRect->h; ++y)
            pixels[(y * surfaceRect->w) + x] = color;

    SDL_BlitSurface(surfaceRect, NULL, screen, &rect);

    SDL_FreeSurface(surfaceRect);
}

// scans through each pixel of the surface and modifies the RGB values
// commenting out green and blue gives a nice red flicker, free to toy with
SDL_Surface* Texture::MakeDamageTexture(string filename)
{
  SDL_Surface* surface = LoadImage(filename);
  
    if(SDL_MUSTLOCK(surface))
    SDL_LockSurface(surface);
    
    Uint32* pixels = (Uint32*)surface->pixels;
    Uint8 red, green, blue, alpha;

  for(int x = 0; x < surface->w; ++x)
      for(int y = 0; y < surface->h; ++y)
      {
            Uint32 color = pixels[(y * surface->w) + x];
            SDL_GetRGBA(color, surface->format, &red, &green, &blue, &alpha);
            red = Minimum(red + COLOR_OFFSET, 255);
            green = Minimum(green + COLOR_OFFSET, 255);
            blue = Minimum(blue + COLOR_OFFSET, 255);
            pixels[(y * surface->w) + x] = SDL_MapRGBA(surface->format, red, green, blue, alpha);
    }
    
    if(SDL_MUSTLOCK(surface))
    SDL_UnlockSurface(surface);

  return surface;
}
