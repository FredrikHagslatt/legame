#ifndef VELOCITY_H
#define VELOCITY_H

#include "glm/glm.hpp"

struct Velocity
{
    double x;
    double y;

    Velocity(double x = 0, double y = 0)
        : x(x), y(y)
    {
    }
    Velocity(glm::vec2 velocity = glm::vec2(0))
        : x(velocity.x), y(velocity.y)
    {
    }


};

#endif