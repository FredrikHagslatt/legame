#ifndef GAME_H
#define GAME_H

#include "entt/entt.hpp"
#include "AssetStore/AssetStore.h"
#include "Constants/Constants.h"
#include <SDL2/SDL.h>
#include <list>

class Game
{
private:
    bool debugMode = false;
    bool isRunning;
    double deltaTime = 0;
    int millisecsPreviousFrame = 0;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect camera;

    entt::registry registry;
    std::unique_ptr<AssetStore> assetStore;

public:
    Game();
    ~Game();
    void Initialize();
    void Run();
    void LoadLevel(int level);
    void LoadMap(std::string spritesheet, std::string map);
    void Setup();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

    static std::list<entt::entity> entitiesToKill;
    static int windowWidth;
    static int windowHeight;
    static int mapWidth;
    static int mapHeight;
};

#endif