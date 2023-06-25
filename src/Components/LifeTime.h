#ifndef LIFETIME_H
#define LIFETIME_H

#include <SDL2/SDL.h>

struct LifeTime
{
    int duration;
    int startTime;

    LifeTime(
        int duration = 0)
        : duration(duration),
          startTime(SDL_GetTicks())
    {
    }
};

#endif