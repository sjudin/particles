#include "rect.h"
#include <iostream>

Rect::Rect(Eigen::Vector2f pos, int w, int h, 
    int r, int g, int b, int a) :
Entity(pos), _w(w), _h(h), _r(r), _g(g), _b(b), _a(a)
{
    rect = { (int)pos(0,0), (int)pos(1,0), _w, _h };
}

void Rect::update(Eigen::Vector2f newPos)
{
    Entity::pos = newPos;

    rect.x = (int)Entity::pos(0,0);
    rect.y = (int)Entity::pos(1,0);
}

void Rect::draw( SDL_Renderer* renderer )
{
    SDL_SetRenderDrawColor(renderer, _r, _g, _b, _a);
    SDL_RenderFillRect(renderer, &rect);
}
