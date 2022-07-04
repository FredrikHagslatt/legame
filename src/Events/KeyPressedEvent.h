#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include <SDL2/SDL.h>
#include <memory>
#include "entt/entt.hpp"

struct KeyPressedEvent
{
    std::shared_ptr<entt::registry> registry;
    SDL_Keycode key;
};

#endif
