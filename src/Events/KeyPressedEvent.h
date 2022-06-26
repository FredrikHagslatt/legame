#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include "entt/entt.hpp"
#include "SDL2/SDL.h"

struct KeyPressedEvent
{
    entt::registry &registry;
    SDL_Event &sdlEvent;
};

entt::sigh<void(KeyPressedEvent)> keyPressedEventEmitter;
entt::sink keyPressedEventListener{keyPressedEventEmitter};

#endif