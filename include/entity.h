#pragma once
#include <eigen3/Eigen/Dense>
#include <SDL2/SDL.h>

/**
 * Base class for atomic objects
 *
 * The entity class keeps track of the position of an object.
 * It also provides an overrideable function for 
 * drawing/rendering the object
 *
 */
class Entity
{
public:
    Entity(Eigen::VectorXf pos);

    // Override this to tell the engine how the 
    // entity should be drawn
    virtual void draw( SDL_Renderer* renderer ) = 0;

    Eigen::VectorXf pos;
    Eigen::Vector2f speed;
    Eigen::Vector2f acc;

    bool isRigid;
};
