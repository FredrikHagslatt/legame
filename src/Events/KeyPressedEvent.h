#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include <SDL2/SDL.h>

class KeyPressedEvent
{
public:
    entt::registry &registry;
    SDL_Keycode key;
    KeyPressedEvent(entt::registry &registry, SDL_Keycode key) : registry(registry), key(key) {}
};

#endif
