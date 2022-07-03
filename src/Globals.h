#ifndef GLOBALS_H
#define GLOBALS_H

#include <list>
#include "entt/entt.hpp"
#include "SDL2/SDL.h"
#include "AssetStore/AssetStore.h"

/*  Move to some clas. Here temporarily */
entt::registry registry;
AssetStore assetStore;
SDL_Renderer *renderer;

std::list<entt::entity> entitiesToKill;
int mapWidth = 0;
int mapHeight = 0;

#endif