// Object.hpp

#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <vector>

#include "Sprite.hpp"

class Object
{
  public:
    Object(std::string keyname);
    ~Object();

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
    static SDL_Rect Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB);
    static bool CheckCollision(Object* objectA, Object* objectB);
    static bool GetAlphaXY(SDL_Surface* surface, int x, int y);

    Sprite* sprite;
    Vector position;
    Vector direction;
    float speed;
    bool dead;
};

#endif
