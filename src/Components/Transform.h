#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Types.h"

struct Transform
{
    vec2f position;
    vec2f scale;
    double rotation;

    Transform(
        vec2f position = vec2f(0, 0),
        vec2f scale = vec2f(1, 1),
        double rotation = 0.0)
        : position(position),
          scale(scale),
          rotation(rotation)
    {
    }
};

#endif