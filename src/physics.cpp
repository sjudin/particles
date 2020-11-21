#include "physics.h"

namespace physics
{
    
    void collide(std::vector<Rect*>& rects_under_test, std::vector<Rect*>& comp_rects) {
        // Choose the current entity and go through all others
        // NOTE: Complexity is pretty bad (O(n^2))
        for (u_int16_t i = 0; i < rects_under_test.size(); i++) {
            for (u_int16_t j = 0; j < comp_rects.size(); j++) {
                // Check that we are not comparing rects with themselves
                if (!(rects_under_test[i] == comp_rects[j]))
                    if (hasCollided(rects_under_test[i], comp_rects[j]))
                        rects_under_test[i]->speed *= -1;
            }
        }
    }

    bool hasCollided(Rect* r1, Rect* r2) {
        // If r1 and r2 are not close enough, no collision
        // has occured
        //
        Eigen::Vector2f left1 = r1->getPos();
        Eigen::Vector2f right1 = r1->getPos() + 
            Eigen::Vector2f(r1->getRect()->w, r1->getRect()->h);

        Eigen::Vector2f left2 = r2->getPos();
        Eigen::Vector2f right2 = r2->getPos() + 
            Eigen::Vector2f(r2->getRect()->w, r2->getRect()->h);

        // If one rectangle is on left side of other 
        if (left1(0) >= right2(0) || left2(0) >= right1(0)) 
            return false; 
      
        // If one rectangle is above other 
        if (left1(1) >= right2(1) || left2(1) >= right1(1)) 
            return false; 
      
        return true;
    }

    void checkProximity(std::vector<Rect*>& rects, Eigen::Vector2f mousePos) {
        
        for(Rect* r : rects) {
            if((r->getPos() - mousePos).norm() < 50) {
                r->setColor(255, 0, 0);
                r->speed *= 2.f;
            }
            else {
                r->setColor(0, 0, 255);
            }
        }

    }

}
