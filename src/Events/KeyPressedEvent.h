#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include <SDL2/SDL.h>
#include "entt/entt.hpp"
#include <memory>

struct KeyPressedEvent
{
    std::shared_ptr<entt::registry> registry;
    SDL_Keycode keycode;
};

#endif