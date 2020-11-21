#pragma once
#include <iostream>
#include "SDL2/SDL.h"
#include <vector>

#include "rect.h"


namespace physics
{
    // How should physics engine work
    // Given a set of entities, compute if they are colliding with eachother
    // and reverse their speed if they are
    //
    // Should also have some notion of mass (at a later point)
    //
    // QUESTION: Should the entity of the physics engine be responsible
    //           for keeping track of things such as velocity and acceleration?
    //               - If the engine does it, we need to keep track of all entities
    //               - If the Rect does it, we might be giving it both visual and
    //                 physics physical attributes (mixing backend/frontend).
    
    // Takes a vector of entity pointers and updates their physics
    // ie reverses their speed if they have collided
    void collide(std::vector<Entity>& entities);
    // void collide(std::vector<Rect>& rects);
    void collide(std::vector<Rect*>& rects_under_test, std::vector<Rect*>& comp_rects);
    void checkProximity(std::vector<Rect*>& rects, Eigen::Vector2f mousePos);

    // Checks if two entities have collided
    // @return -1: No collision
    //          0: Left wall 
    //          1: Right wall 
    //          2: Top wall 
    //          3: Bottom wall 
    // bool hasCollided(Entity& e1, Entity& e2);
    bool hasCollided(Rect* r1, Rect* r2);
}
