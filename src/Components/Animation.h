#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>

struct Animation
{
    int numFrames;
    int currentFrame;
    int frameRateSpeed;
    bool isLoop;
    int startTime;

    Animation(
        int numFrames = 1,
        int frameRateSpeed = 1,
        int isLoop = true)
        : numFrames(numFrames),
          currentFrame(1),
          frameRateSpeed(frameRateSpeed),
          isLoop(isLoop),
          startTime(SDL_GetTicks())
    {
    }
};

#endif