#ifndef KEYBOARDCONTROLLED_H
#define KEYBOARDCONTROLLED_H

#include <Types.h>

struct KeyboardControlled
{
    vec2f upVelocity;
    vec2f rightVelocity;
    vec2f downVelocity;
    vec2f leftVelocity;

    KeyboardControlled(
        vec2f upVelocity = vec2f(0),
        vec2f rightVelocity = vec2f(0),
        vec2f downVelocity = vec2f(0),
        vec2f leftVelocity = vec2f(0))
        : upVelocity(upVelocity),
          rightVelocity(rightVelocity),
          downVelocity(downVelocity),
          leftVelocity(leftVelocity)
    {
    }
};

#endif