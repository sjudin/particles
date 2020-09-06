#include "physics.h"

namespace physics
{
    
    void collide(std::vector<Entity*> entities) {
        // Choose the current entity and go through all others
        // NOTE: Complexity is pretty bad (O(n^2))
        for (unsigned int i = 0; i < entities.size(); i++) {
            for (unsigned int j = 0; j < entities.size(); j++) {
                // Dont check collision with ones self
                if (i != j) 
                    if (hasCollided(entities[i], entities[j]) == true && !entities[i]->isRigid) 
                    {
                        float nom   = (entities[i]->speed - entities[j]->speed).dot(entities[i]->pos - entities[j]->pos);
                        float denom = (entities[i]->pos - entities[j]->pos).squaredNorm();
                        Eigen::Vector2f last  = (entities[i]->pos - entities[j]->pos);

                        // Calculate perfect elastic collision with m=1
                        entities[i]->speed = -(entities[i]->speed - nom/denom*last);
                    }
                              
            }
        }
    }

    bool hasCollided(Entity* e1, Entity* e2)
    {
        // Cast to Rect, (Should be more general
        // than this in the future, will need to refactor
        Rect* r1 = dynamic_cast<Rect*>(e1);
        Rect* r2 = dynamic_cast<Rect*>(e2);

        // If r1 and r2 are not close enough, no collision
        // has occured
        Eigen::Vector2f r1Mid = r1->getPos() 
          + Eigen::Vector2f(r1->getRect()->w/2, 
                            r1->getRect()->h/2); // r1 midpoint

        Eigen::Vector2f r2Mid = r2->getPos() 
          + Eigen::Vector2f(r2->getRect()->w/2, 
                            r2->getRect()->h/2); // r2 midpoint

        r1Mid = r2Mid - r1Mid;
        if ( ( std::abs(r1Mid(0,0)) > r1->getRect()->w/2 + r2->getRect()->w/2 ) ||
             ( std::abs(r1Mid(1,0)) > r1->getRect()->h/2 + r2->getRect()->h/2 ) )
            return false;

        return true;
    }

}
