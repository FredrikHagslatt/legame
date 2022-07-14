#ifndef PROJECTILEEMITTER_H
#define PROJECTILEEMITTER_H

#include "Types.h"

struct ProjectileEmitter
{
    double speed;
    vec2f direction;
    int repeatFrequency;
    int duration;
    int hitPercentDamage;
    bool isFriendly;
    bool inheritDirection;
    int lastEmissionTime;

    ProjectileEmitter(
        double speed = 0,
        vec2f direction = vec2f(0),
        int repeatFrequency = 0,
        int duration = 10000,
        int hitPercentDamage = 10,
        bool isFriendly = false,
        bool inheritDirection = false)
        : speed(speed),
          direction(direction),
          repeatFrequency(repeatFrequency),
          duration(duration),
          hitPercentDamage(hitPercentDamage),
          isFriendly(isFriendly),
          inheritDirection(inheritDirection)
    {
        lastEmissionTime = SDL_GetTicks();
    }
};

#endif