#pragma once
#include "entity.h"

class Rect : public Entity
{
public:
    Rect(Eigen::Vector2f pos, int w, int h,
         int r, int g, int b, int a);

    inline Eigen::Vector2f getPos() { return Entity::pos; };

    void draw( SDL_Renderer* renderer ) override;
    void update(Eigen::Vector2f newPos);

    inline SDL_Rect* getRect() { return &rect; };

private:
    int _w, _h;
    int _r, _g, _b, _a;
    SDL_Rect rect;
};
