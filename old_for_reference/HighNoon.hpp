#ifndef HIGH_NOON_H
#define HIGH_NOON_H

#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "SoundManager.hpp"
#include "GraphicsManager.hpp"

#include "scenes/SceneManager.hpp"
#include "scenes/Menu/MenuRoot.hpp"
#include "scenes/Hub.hpp"
#include "scenes/StardewTemplate.hpp"
#include "scenes/MapEditor.hpp"

class HighNoon {
private:

	SceneManager m_sceneManager;
	Player* m_player;
	uint64_t m_now_time;

public:
	HighNoon();
	~HighNoon();
	bool GameCycle();
};

#endif //HIGH_NOON_H