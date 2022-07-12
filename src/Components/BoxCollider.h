#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Types.h"
#include "Constants.h"

struct BoxCollider
{
    int width;
    int height;
    vec2f offset;

    BoxCollider(
        int width = 0,
        int height = 0,
        vec2f offset = vec2f(0))
        : width(width * SCALE),
          height(height * SCALE),
          offset(offset * SCALE)
    {
    }
};

#endif