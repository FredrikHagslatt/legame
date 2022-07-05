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
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SceneManager m_sceneManager;
    std::shared_ptr<entt::registry> m_registry;
    std::shared_ptr<AssetStore> m_assetStore;
    entt::dispatcher m_dispatcher{};

    // entt::sigh<void(KeyPressedEvent)> keyPressedEventEmitter;
    //  entt::sink keyPressedEventListener;
    //  entt::sink keyPressedEventListener{keyPressedEventEmitter};

    double ElapsedTime();
    void Setup();
    void Update();
    void ProcessInput();

public:
    static int mapWidth;
    static int mapHeight;
    Game();
    ~Game();
    void Initialize();
    void Run();
    void Destroy();
};

#endif