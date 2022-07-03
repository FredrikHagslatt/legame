#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include "entt/entt.hpp"
#include "SDL2/SDL.h"

struct KeyPressedEvent
{
    entt::registry &registry;
    SDL_Keycode &key; //sdlEvent.key.keysym.sym
};

entt::sigh<void(KeyPressedEvent)> keyPressedEventEmitter;
entt::sink keyPressedEventListener{keyPressedEventEmitter};

#endif