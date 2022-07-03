#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include <SDL2/SDL.h>

class KeyPressedEvent
{
public:
    SDL_Keycode key;
    KeyPressedEvent(SDL_Keycode key) : key(key) {}
};

#endif
