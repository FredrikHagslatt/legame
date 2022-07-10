#ifndef VELOCITY_H
#define VELOCITY_H

#include "Types.h"

struct Velocity
{
    double speed;
    vec2f direction;

    Velocity(double speed = 0)
        : speed(speed), direction(vec2f(0))
    {
    }
    Velocity(double speed = 0, vec2f direction = vec2f(0))
        : speed(speed), direction(direction)
    {
    }
};

#endif