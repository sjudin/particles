#include "window.h"
#include "rect.h"
#include <string>
#include <stdlib.h>
#include <vector>
#include "physics.h"
#include <random>
#include <chrono>
#include <memory>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct ScopedMicroTimer
{
    std::chrono::high_resolution_clock::time_point t0;
    std::function<void(int)> cb;
    
    ScopedMicroTimer(std::function<void(int)> callback)
        : t0(std::chrono::high_resolution_clock::now())
        , cb(callback)
    {
    }
    ~ScopedMicroTimer(void)
    {
        auto  t1 = std::chrono::high_resolution_clock::now();
        auto micros = std::chrono::duration_cast
            <std::chrono::microseconds>(t1-t0).count();
 
        cb(micros);
    }
};

struct Results
{
    void operator()(int us)
    {
        std::cout << "Microseconds: " << us << std::endl;
    }
};


int main()
{
    Window window("Test Window", WINDOW_WIDTH, WINDOW_HEIGHT);

    // Edges of arena
    Rect ground(Eigen::Vector2f(0, WINDOW_HEIGHT-10), WINDOW_WIDTH, 10, 0, 0, 0, 255);
    ground.isRigid = true;
    Rect ceiling(Eigen::Vector2f(0, 0), WINDOW_WIDTH, 10, 0, 0, 0, 255);
    ceiling.isRigid = true;
    Rect leftWall(Eigen::Vector2f(0, 0), 10, WINDOW_HEIGHT, 0, 0, 0, 255);
    leftWall.isRigid = true;
    Rect rightWall(Eigen::Vector2f(WINDOW_WIDTH-10, 0), 10, WINDOW_HEIGHT, 0, 0, 0, 255);
    rightWall.isRigid = true;

    std::vector<Rect*> statics;

    statics.push_back(&ground);
    statics.push_back(&ceiling);
    statics.push_back(&leftWall);
    statics.push_back(&rightWall);

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distributionX(20, WINDOW_WIDTH-20);
    std::uniform_real_distribution<float> distributionY(20, WINDOW_HEIGHT-20);

    // float xPos = distributionX(generator);
    // float yPos = distributionY(generator);

    std::vector<Rect*> rects;

    // Make sure that these dont go out of scope, use a unique ptr or something?
    // Rect r = Rect(Eigen::Vector2f(xPos, yPos), 5, 5, 0, 255, 255, 255);

    for(u_int16_t i = 0; i < 800; i++) {
        float xPos = distributionX(generator);
        float yPos = distributionY(generator);

        rects.push_back(new Rect(Eigen::Vector2f(xPos, yPos), 4, 4, 0, 0, 0, 255));
    }
    
    float dt = 0.5;
    int x,y;

    while(!window.isClosed())
    {
        // Draw rect
        SDL_GetMouseState(&x, &y);

        for(unsigned int i = 0; i < rects.size(); i++)
        {
            rects[i]->speed += rects[i]->acc*dt;
            rects[i]->update(rects[i]->getPos() + rects[i]->speed*dt);
        }

        Results results;
        physics::collide(rects, statics, dt);
        {
            // ScopedMicroTimer timer(results);

            physics::collide(rects, rects, dt);
        }
        physics::checkProximity(rects, Eigen::Vector2f(x,y));

        // Update moving and static parts
        for(Rect* r : rects) r->draw(window.getRenderer());
        for(Rect* r : statics) r->draw(window.getRenderer());

        // Clear the window
        window.clear();
        
        // Check event queue
        window.pollEvents();

        SDL_Delay(10);
    }

    return 0;
}
