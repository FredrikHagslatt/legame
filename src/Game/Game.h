#ifndef GAME_H
#define GAME_H

#include "entt/entt.hpp"
#include "AssetStore/AssetStore.h"
#include "SceneManager/SceneManager.h"
#include <SDL2/SDL.h>
#include <list>
#include <unordered_set>
#include "DevTools/DevTools.h"

class Game
{
private:
    bool isRunning;
    double deltaTime = 0;
    int millisecsPreviousFrame = 0;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SceneManager m_sceneManager;
    std::shared_ptr<entt::registry> m_registry;
    std::shared_ptr<AssetStore> m_assetStore;

    double
    ElapsedTime();
    void Setup();
    void Update();
    void ProcessInput();

public:
    Game();
    ~Game();
    void Initialize();
    void Run();
    void Destroy();

    static std::list<entt::entity> entitiesToKill;
};

#endif