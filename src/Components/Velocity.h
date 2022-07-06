#ifndef VELOCITY_H
#define VELOCITY_H

#include "Types.h"

struct Velocity
{
    double x;
    double y;

    Velocity(double x = 0, double y = 0)
        : x(x), y(y)
    {
    }
    Velocity(vec2f velocity = vec2f(0))
        : x(velocity.x), y(velocity.y)
    {
    }
};

#endif