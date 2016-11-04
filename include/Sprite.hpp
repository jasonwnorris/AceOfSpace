// Sprite.hpp

#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__

// AOS Includes
#include "Vector2f.hpp"
#include "Texture.hpp"

class Sprite
{
  public:
    Sprite(const std::string& p_Keyname);

    void Update(float p_DeltaTime);
    void Render(SDL_Renderer* p_Renderer, Vector2f p_Position);

    SDL_Rect GetFrameBounds();

    void SetTextureIndex(int p_Index);

    Texture* m_Texture;
    Vector2f m_Origin;

  private:
    int m_Frame;
    float m_FrameTimeRemaining;
    int m_TextureIndex;
};

#endif
