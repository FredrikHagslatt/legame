#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>

struct Animation
{
    int numFrames;
    int currentFrame;
    int frameRateSpeed;
    bool isLoop;
    bool hasDirections;
    int startTime;

    Animation(
        int numFrames = 1,
        int frameRateSpeed = 1,
        int isLoop = true,
        bool hasDirections = false)
        : numFrames(numFrames),
          currentFrame(1),
          frameRateSpeed(frameRateSpeed),
          isLoop(isLoop),
          hasDirections(hasDirections),
          startTime(SDL_GetTicks())
    {
    }
};

#endif