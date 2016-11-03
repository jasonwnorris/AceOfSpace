// Sprite.hpp

#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__

// AOS Includes
#include "Vector2f.hpp"
#include "Texture.hpp"

class Sprite
{
  public:
    Sprite(const std::string& keyname);

    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer, Vector2f position);

    SDL_Rect GetFrameBounds();

    void SetTextureIndex(int index);

    Texture* texture;
    Vector2f origin;

  private:
    int frame;
    float frameTimeRemaining;

    int textureIndex;
};

#endif
