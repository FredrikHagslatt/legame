#ifndef KEYRELEASEDEVENT_H
#define KEYRELEASEDEVENT_H

#include <SDL2/SDL.h>
#include "entt/entt.hpp"
#include <memory>

struct KeyReleasedEvent
{
    std::shared_ptr<entt::registry> registry;
    SDL_Keycode keycode;
};

#endif
