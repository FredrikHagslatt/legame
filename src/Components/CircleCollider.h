#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "Types.h"
#include "Constants.h"

struct CircleCollider
{
    int radius;
    vec2f offset;

    CircleCollider(
        int radius = 0,
        vec2f offset = vec2f(0))
        : radius(radius * SCALE),
          offset(offset * SCALE)
    {
    }
};

#endif