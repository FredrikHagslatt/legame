#ifndef PROJECTILEEMITTER_H
#define PROJECTILEEMITTER_H

#include "Types.h"

struct ProjectileEmitter
{
    vec2f projectileVelocity;
    int repeatFrequency;
    int projectileDuration;
    int hitPercentDamage;
    bool isFriendly;
    int lastEmissionTime;

    ProjectileEmitter(
        vec2f projectileVelocity = vec2f(0),
        int repeatFrequency = 0,
        int projectileDuration = 10000,
        int hitPercentDamage = 10,
        bool isFriendly = false)
        : projectileVelocity(projectileVelocity),
          repeatFrequency(repeatFrequency),
          projectileDuration(projectileDuration),
          hitPercentDamage(hitPercentDamage),
          isFriendly(isFriendly)
    {
        lastEmissionTime = SDL_GetTicks();
    }
};

#endif