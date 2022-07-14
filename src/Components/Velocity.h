#ifndef VELOCITY_H
#define VELOCITY_H

#include "Types.h"

struct Velocity
{
    double speed;
    vec2f direction;
    vec2f lastNonZeroDirection;

    Velocity(double speed = 0, vec2f direction = vec2f(0), vec2f lastNonZeroDirection = vec2f(0.0, 1.0))
        : speed(speed), direction(direction), lastNonZeroDirection(lastNonZeroDirection)
    {
    }
};

#endif