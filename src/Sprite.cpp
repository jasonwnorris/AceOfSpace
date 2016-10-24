// Sprite.cpp //
#include "Sprite.hpp"

Sprite::Sprite(std::string keyname)
{
  texture = Texture::TextureList[keyname];
  origin = Vector(texture->tileWidth / 2, texture->tileHeight / 2);
  frame = 0;
  frameTimeRemaining = texture->frameInterval;
  textureIndex = 0;
}

void Sprite::Update(float deltaTime)
{
  frameTimeRemaining -= deltaTime;
  if (frameTimeRemaining < 0)
  {
    frame++;
    frame %= texture->frameCount;
    frameTimeRemaining = texture->frameInterval;
  }
}

// render either the plain or damaged texture
void Sprite::Render(SDL_Renderer* renderer, Vector position)
{
  SDL_Texture* t = texture->textures[textureIndex];

  SDL_Rect clip = GetFrameBounds();

  SDL_Rect location;
  location.x = (Sint16)(position.X - origin.X);
  location.y = (Sint16)(position.Y - origin.Y);
  location.w = clip.w;
  location.h = clip.h;

  SDL_RenderCopy(renderer, t, &clip, &location);
}

// grabs a SDL_Rect around the currect frame of animation we're on
SDL_Rect Sprite::GetFrameBounds()
{
  SDL_Rect frameBounds;
  frameBounds.x = frame % texture->tilesX * texture->tileWidth;
  frameBounds.y = frame / texture->tilesX * texture->tileHeight;
  frameBounds.w = texture->tileWidth;
  frameBounds.h = texture->tileHeight;

  return frameBounds;
}

// switch to damage texture if it has one
void Sprite::SetTextureIndex(int index)
{
  if (texture->collidable)
    textureIndex = index;
}
