#include "entity.h"

Entity::Entity(Eigen::VectorXf pos):
  pos(pos)
{
  speed = Eigen::Vector2f(0,0);
  acc = Eigen::Vector2f(0,0);
}

