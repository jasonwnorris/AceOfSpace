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
    Object(const std::string& keyname);
    virtual ~Object();

    static std::vector<Object*> ObjectList;
    static std::vector<Object*> ObjectAddList;

    static void UpdateObjects(float deltaTime);
    virtual void Update(float deltaTime);

    static void RenderObjects(SDL_Renderer* renderer);
    virtual void Render(SDL_Renderer* renderer);

    static void AddNew();
    static void RemoveDead();
    static void RemoveAll();
    virtual void Remove();

    void Move(Vector amount);

    SDL_Rect GetBounds();
    SDL_Rect NormalizeBounds(const SDL_Rect& rect);
    static bool CheckCollision(Object* objectA, Object* objectB);
    static bool GetAlphaXY(Texture* texture, int x, int y);

    Sprite* sprite;
    Vector position;
    Vector direction;
    float speed;
    bool dead;
};

#endif
