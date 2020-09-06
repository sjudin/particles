#include "window.h"
#include "rect.h"
#include <string>
#include <stdlib.h>
#include <vector>
#include "physics.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char* argv[])
{
    Window window("Test Window", WINDOW_WIDTH, WINDOW_HEIGHT);

    // Rect rect1(Eigen::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2), 25, 25, 255, 255, 255, 255);
    // Rect rect2(Eigen::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2-5), 25, 25, 0, 255, 255, 255);

    // Edges of arena
    Rect ground(Eigen::Vector2f(0, WINDOW_HEIGHT-10), WINDOW_WIDTH, 10, 0, 0, 0, 255);
    ground.isRigid = true;
    Rect ceiling(Eigen::Vector2f(0, 0), WINDOW_WIDTH, 10, 0, 0, 0, 255);
    ceiling.isRigid = true;
    Rect leftWall(Eigen::Vector2f(0, 0), 10, WINDOW_HEIGHT, 0, 0, 0, 255);
    leftWall.isRigid = true;
    Rect rightWall(Eigen::Vector2f(WINDOW_WIDTH-10, 0), 10, WINDOW_HEIGHT, 0, 0, 0, 255);
    rightWall.isRigid = true;

    std::vector<Entity*> entities;
    entities.push_back(&ground);
    entities.push_back(&ceiling);
    entities.push_back(&leftWall);
    entities.push_back(&rightWall);
    
    Rect rect1(Eigen::Vector2f(50, WINDOW_HEIGHT/2), 25, 25, 255, 255, 255, 255);
    rect1.speed = Eigen::Vector2f::Random();
    rect1.acc = Eigen::Vector2f::Random();
    rect1.isRigid = false;
    Rect rect2(Eigen::Vector2f(100, WINDOW_HEIGHT/2-5), 25, 25, 0, 255, 255, 255);
    rect2.speed = Eigen::Vector2f::Random();
    rect1.acc = Eigen::Vector2f::Random();
    rect2.isRigid = false;
    Rect rect3(Eigen::Vector2f(150, WINDOW_HEIGHT/2-5), 25, 25, 0, 255, 255, 255);
    rect3.speed = Eigen::Vector2f::Random();
    rect1.acc = Eigen::Vector2f::Random();
    rect3.isRigid = false;
    Rect rect4(Eigen::Vector2f(200, WINDOW_HEIGHT/2-5), 25, 25, 0, 255, 255, 255);
    rect4.speed = Eigen::Vector2f::Random();
    rect1.acc = Eigen::Vector2f::Random();
    rect4.isRigid = false;
    Rect rect5(Eigen::Vector2f(250, WINDOW_HEIGHT/2-5), 25, 25, 0, 255, 255, 255);
    rect5.speed = Eigen::Vector2f::Random();
    rect1.acc = Eigen::Vector2f::Random();
    rect5.isRigid = false;

    entities.push_back(&rect1);
    entities.push_back(&rect2);
    entities.push_back(&rect3);
    entities.push_back(&rect4);
    entities.push_back(&rect5);

    float dt = 0.5;
    int x,y;

    while(!window.isClosed())
    {
        // Draw rect
        SDL_GetMouseState(&x, &y);
        // dynamic_cast<Rect*>(entities[5])->update(Eigen::Vector2f(x,y));
        physics::collide(entities);

        for(unsigned int i = 0; i < entities.size(); i++)
        {
            Rect* r = dynamic_cast<Rect*>(entities[i]);
            r->speed += r->acc*dt;
            r->update(r->getPos() + r->speed*dt);
            // std::cout << r->pos << std::endl << std::endl;
        }
        for(Entity* e : entities)
            e->draw(window.getRenderer());


        // Clear the window
        window.clear();
        
        // Check event queue
        window.pollEvents();

        SDL_Delay(10);
    }

    return 0;
}
