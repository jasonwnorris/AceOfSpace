// Object.hpp

#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

// STL Includes
#include <vector>
// AOS Includes
#include "Sprite.hpp"

class Object
{
  public:
    Object(const std::string& p_Keyname);
    virtual ~Object();

    static std::vector<Object*> ObjectList;
    static std::vector<Object*> ObjectAddList;

    static void UpdateObjects(float p_DeltaTime);
    virtual void Update(float p_DeltaTime);

    static void RenderObjects(SDL_Renderer* p_Renderer);
    virtual void Render(SDL_Renderer* p_Renderer);

    static void AddNew();
    static void RemoveDead();
    static void RemoveAll();
    virtual void Remove();

    void Move(Vector2f amount);

    SDL_Rect GetBounds();
    SDL_Rect NormalizeBounds(const SDL_Rect& p_Rect);
    static bool CheckCollision(Object* p_ObjectA, Object* p_ObjectB);
    static bool GetAlphaXY(Texture* p_Texture, int p_X, int p_Y);

    Sprite* m_Sprite;
    Vector2f m_Position;
    Vector2f m_Direction;
    float m_Speed;
    bool m_IsDead;
};

#endif
