#ifndef GAME_H
#define GAME_H

#include "entt/entt.hpp"
#include "AssetStore/AssetStore.h"
#include "SceneManager/SceneManager.h"
#include <SDL2/SDL.h>
#include <list>
#include "Events/CollisionEvent.h"
#include "Events/KeyPressedEvent.h"

class Game
{
private:
    bool isRunning;
    double deltaTime = 0;
    int millisecsPreviousFrame = 0;
    SDL_Window *window;
    //    SDL_Renderer *renderer;

    SceneManager m_sceneManager;
    //    entt::registry registry;
    //    std::unique_ptr<AssetStore> assetStore;
    double ElapsedTime();
    void Setup();
    void Update();
    void ProcessInput();

public:
    Game();
    ~Game();
    void Initialize();
    void Run();
    void Destroy();
};

#endif