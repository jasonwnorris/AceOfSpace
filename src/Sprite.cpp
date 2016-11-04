// Sprite.cpp

// AOS Includes
#include "Sprite.hpp"

Sprite::Sprite(const std::string& p_Keyname)
{
  m_Texture = Texture::TextureList[p_Keyname];
  m_Origin = Vector2f(m_Texture->m_TileWidth / 2.0f, m_Texture->m_TileHeight / 2.0f);
  m_Frame = 0;
  m_FrameTimeRemaining = m_Texture->m_FrameInterval;
  m_TextureIndex = 0;
}

void Sprite::Update(float p_DeltaTime)
{
  m_FrameTimeRemaining -= p_DeltaTime;
  if (m_FrameTimeRemaining < 0.0f)
  {
    ++m_Frame;
    m_Frame %= m_Texture->m_FrameCount;
    m_FrameTimeRemaining = m_Texture->m_FrameInterval;
  }
}

void Sprite::Render(SDL_Renderer* renderer, Vector2f position)
{
  SDL_Texture* texture = m_Texture->m_Textures[m_TextureIndex];

  SDL_Rect clip = GetFrameBounds();

  SDL_Rect location;
  location.x = (Sint16)(position.X - m_Origin.X);
  location.y = (Sint16)(position.Y - m_Origin.Y);
  location.w = clip.w;
  location.h = clip.h;

  SDL_RenderCopy(renderer, texture, &clip, &location);
}

SDL_Rect Sprite::GetFrameBounds()
{
  SDL_Rect m_FrameBounds;
  m_FrameBounds.x = m_Frame % m_Texture->m_TilesX * m_Texture->m_TileWidth;
  m_FrameBounds.y = m_Frame / m_Texture->m_TilesX * m_Texture->m_TileHeight;
  m_FrameBounds.w = m_Texture->m_TileWidth;
  m_FrameBounds.h = m_Texture->m_TileHeight;

  return m_FrameBounds;
}

void Sprite::SetTextureIndex(int p_Index)
{
  if (m_Texture->m_IsCollidable)
  {
    m_TextureIndex = p_Index;
  }
}
