#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>

struct Projectile
{
    bool isFriendly;
    int hitPercentDamage;
    int duration;
    int startTime;

    Projectile(
        bool isFriendly = false,
        int hitPercentDamage = 0,
        int duration = 0)
        : isFriendly(isFriendly),
          hitPercentDamage(hitPercentDamage),
          duration(duration),
          startTime(SDL_GetTicks())

    {
    }
};

#endif