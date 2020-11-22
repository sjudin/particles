#include "physics.h"

namespace physics
{
    
    void collide(std::vector<Rect*>& rects_under_test, 
                 std::vector<Rect*>& comp_rects,
                 float dt)
    {
        // Choose the current entity and go through all others
        // NOTE: Complexity is pretty bad (O(n^2))
        
        for(Rect* rect_under_test : rects_under_test)
            for (Rect* comp_rect : comp_rects)
                if (!(rect_under_test == comp_rect))
                    if (hasCollided(rect_under_test, comp_rect, dt))
                    {
                        //TODO
                        // Calculate speed of the objects better after a collision
                        rect_under_test->speed *= -0.9f;
                    }
    }

    bool hasCollided(Rect* r1, Rect* r2, float dt) {

        Eigen::Vector2f left1 = r1->getPos();
        Eigen::Vector2f right1 = r1->getPos() + 
            Eigen::Vector2f(r1->getRect()->w, r1->getRect()->h);

        Eigen::Vector2f left2 = r2->getPos();
        Eigen::Vector2f right2 = r2->getPos() + 
            Eigen::Vector2f(r2->getRect()->w, r2->getRect()->h);

        if (left1(0)+r1->speed(0)*dt >= right2(0) 
            || left2(0) >= right1(0)+r1->speed(0)*dt) 
            return false; 
      
        // If one rectangle is above other 
        if (left1(1)+r1->speed(1)*dt >= right2(1) 
            || left2(1) >= right1(1)+r1->speed(1)*dt) 
            return false; 
      
        return true;
    }

    void checkProximity(std::vector<Rect*>& rects, Eigen::Vector2f mousePos) {
        
        for(Rect* r : rects) {
            Eigen::Vector2f rect_to_mouse = r->getPos() - mousePos;
            if(rect_to_mouse.norm() < 50) {
                r->setColor(255, 0, 0);
                r->acc = rect_to_mouse/10;
            }
            else {
                r->acc = Eigen::Vector2f(0,0);
                r->setColor(0, 0, 255);
            }
        }

    }

}
