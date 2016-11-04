// Sprite.cpp

// AOS Includes
#include "Sprite.hpp"

Sprite::Sprite(const std::string& p_Keyname)
{
  m_Texture = Texture::TextureList[p_Keyname];
  m_Origin = Vector2f(m_Texture->GetTileWidth() / 2.0f, m_Texture->GetTileHeight() / 2.0f);
  m_Frame = 0;
  m_FrameTimeRemaining = m_Texture->GetFrameInterval();
  m_TextureIndex = 0;
}

Texture* Sprite::GetTexture() const
{
  return m_Texture;
}

const Vector2f& Sprite::GetOrigin() const
{
  return m_Origin;
}

void Sprite::Update(float p_DeltaTime)
{
  m_FrameTimeRemaining -= p_DeltaTime;
  if (m_FrameTimeRemaining < 0.0f)
  {
    ++m_Frame;
    m_Frame %= m_Texture->GetFrameCount();
    m_FrameTimeRemaining = m_Texture->GetFrameInterval();
  }
}

void Sprite::Render(SDL_Renderer* p_Renderer, Vector2f p_Position)
{
  SDL_Rect clip = GetFrameBounds();

  SDL_Rect location;
  location.x = static_cast<int>(p_Position.X - m_Origin.X);
  location.y = static_cast<int>(p_Position.Y - m_Origin.Y);
  location.w = clip.w;
  location.h = clip.h;

  SDL_RenderCopy(p_Renderer, m_Texture->GetTexture(m_TextureIndex), &clip, &location);
}

SDL_Rect Sprite::GetFrameBounds()
{
  SDL_Rect m_FrameBounds;
  m_FrameBounds.x = m_Frame % m_Texture->GetTilesX() * m_Texture->GetTileWidth();
  m_FrameBounds.y = m_Frame / m_Texture->GetTilesX() * m_Texture->GetTileHeight();
  m_FrameBounds.w = m_Texture->GetTileWidth();
  m_FrameBounds.h = m_Texture->GetTileHeight();

  return m_FrameBounds;
}

void Sprite::SetTextureIndex(int p_Index)
{
  if (m_Texture->IsCollidable())
  {
    m_TextureIndex = p_Index;
  }
}
