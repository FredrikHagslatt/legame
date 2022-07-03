#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>

#include "entt/entt.hpp"
#include "Logger/Logger.h"
#include <glm/glm.hpp>

#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Components/Velocity.h"
#include "Components/Sprite.h"
#include "Components/Animation.h"
#include "Components/BoxCollider.h"
#include "Components/KeyboardControlled.h"
#include "Components/ProjectileEmitter.h"
#include "Components/Health.h"
#include "Components/TextLabel.h"

#include "Systems/AnimationSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/KeyboardControlSystem.h"
#include "Systems/ProjectileEmitSystem.h"
#include "Systems/ProjectileLifecycleSystem.h"
#include "Systems/CameraMovementSystem.h"
#include "Systems/DamageSystem.h"
#include "Systems/CollisionSystem.h"

#include "Systems/RenderSystem.h"
#include "Systems/RenderHealthSystem.h"
#include "Systems/RenderTextSystem.h"
#include "Systems/RenderColliderSystem.h"

#include "Events/KeyPressedEvent.h"
#include "Events/CollisionEvent.h"

int Game::mapWidth;
int Game::mapHeight;
std::list<entt::entity> Game::entitiesToKill;

Game::Game()
{
    isRunning = false;
    assetStore = std::make_unique<AssetStore>();
    Logger::Info("Game Created!");
}

Game::~Game()
{
    Logger::Info("Game Destroyed!");
}

void Game::Initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Fatal("Error initializing SDL.");
        return;
    }

    if (TTF_Init() != 0)
    {
        Logger::Fatal("Error initializing TTF.");
        return;
    }

//    windowWidth = 800;  // displayMode.w;
//    windowHeight = 600; // displayMode.h;

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOWWIDTH,
        WINDOWHEIGHT,
        SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        Logger::Fatal("Error creating SDL window.");
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        Logger::Fatal("Error creating SDL renderer.");
    }

    camera.x = 0;
    camera.y = 0;
    camera.w = WINDOWWIDTH;
    camera.h = WINDOWHEIGHT;

    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;
}

void Game::ProcessInput()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
            if (sdlEvent.key.keysym.sym == SDLK_d)
            {
                debugMode = !debugMode;

                if (debugMode)
                {
                    Logger::Info("Debug mode activated");
                }
                else
                {
                    Logger::Info("Debug mode dectivated");
                }
            }

            KeyPressedEvent keyPressedEvent{registry, sdlEvent.key.keysym.sym};
            keyPressedEventEmitter.publish(keyPressedEvent);
            break;
        }
    }
}

void Game::LoadMap(std::string spritesheet, std::string map)
{
    assetStore->AddTexture(renderer, spritesheet, spritesheet);

    int mapNumCols = 0;
    int mapNumRows = 0;

    std::fstream mapFile;
    mapFile.open(map);

    //Get map dimensions
    std::string line;
    while(std::getline(mapFile, line))
    {
        if (mapNumCols == 0)
        {
            mapNumCols = (line.size() + 1) / 3;
        }
        else{
            if (mapNumCols != (line.size() + 1) / 3)
            {
                Logger::Fatal("Map is fucked! Row length not matching");
            }
        }
        mapNumRows++;
    }


    mapFile.clear();
    mapFile.seekg(0);//Go to start of file again.

    Logger::Info("Mapsize: " + std::to_string(mapNumCols) + " * " + std::to_string(mapNumRows));

    mapWidth = mapNumCols * TILESIZE * SCALE;
    mapHeight = mapNumRows * TILESIZE * SCALE;


    glm::vec2 offset;
    if (mapWidth < WINDOWWIDTH)
    {
        offset.x = (WINDOWWIDTH - mapWidth) / 2;
    }
    if (mapHeight < WINDOWHEIGHT)
    {
        offset.y = (WINDOWHEIGHT - mapHeight) / 2;
    }


    //Read map, create tiles.
    for (int y = 0; y < mapNumRows; y++)
    {
        for (int x = 0; x < mapNumCols; x++)
        {
            char ch;
            mapFile.get(ch);
            int srcRectY = std::atoi(&ch) * TILESIZE;
            mapFile.get(ch);
            int srcRectX = std::atoi(&ch) * TILESIZE;
            mapFile.ignore();

            const auto tile = registry.create();
            registry.emplace<Transform>(tile, glm::vec2(x * (SCALE * TILESIZE) + offset.x, y * (SCALE * TILESIZE) + offset.y), glm::vec2(SCALE, SCALE), 0.0);
            registry.emplace<Sprite>(tile, spritesheet, TILESIZE, TILESIZE, 0, false, srcRectX, srcRectY);
        }
    }

    mapFile.close();
}

void Game::LoadLevel(int level)
{

    assetStore->AddTexture(renderer, "spike-image", "assets/images/Spike.png");
    assetStore->AddTexture(renderer, "tank-image", "assets/images/tank-panther-right.png");
    assetStore->AddTexture(renderer, "truck-image", "assets/images/truck-ford-right.png");
    assetStore->AddTexture(renderer, "tree-image", "assets/images/tree.png");
    assetStore->AddTexture(renderer, "chopper-image", "assets/images/chopper-spritesheet.png");
    assetStore->AddTexture(renderer, "radar-image", "assets/images/radar.png");
    assetStore->AddTexture(renderer, "bullet-image", "assets/images/bullet.png");

    assetStore->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
    assetStore->AddFont("pico8-font-5", "assets/fonts/pico8.ttf", 5);
    assetStore->AddFont("pico8-font-10", "assets/fonts/pico8.ttf", 10);

    LoadMap("assets/tilemaps/ground_tiles.png", "assets/tilemaps/hub.map");

    const auto player = registry.create();
    registry.emplace<Player_Tag>(player);
    registry.emplace<StayOnMap_Tag>(player);
    registry.emplace<Transform>(player, glm::vec2(200.0, 400.0), glm::vec2(4.0, 4.0), 0.0);
    registry.emplace<Velocity>(player, 0.0, 0.0);
    registry.emplace<Sprite>(player, "spike-image", 16, 32, 10);
    registry.emplace<Animation>(player, 5, 5, true);
    registry.emplace<KeyboardControlled>(player, glm::vec2(0, -200), glm::vec2(200, 0), glm::vec2(0, 200), glm::vec2(-200, 0));
    registry.emplace<ProjectileEmitter>(player, glm::vec2(300.0, 300.0), 0, 10000, 10, true);
    registry.emplace<Health>(player, 100);
    registry.emplace<BoxCollider>(player, 16, 32);

    const auto chopper = registry.create();
    registry.emplace<StayOnMap_Tag>(chopper);
    registry.emplace<Transform>(chopper, glm::vec2(100.0, 100.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Velocity>(chopper, 50.0, 0.0);
    registry.emplace<Sprite>(chopper, "chopper-image", 32, 32, 10);
    registry.emplace<Animation>(chopper, 2, 12, true);
    registry.emplace<ProjectileEmitter>(chopper, glm::vec2(300.0, 300.0), 0, 10000, 10, true);
    registry.emplace<Health>(chopper, 100);
    registry.emplace<BoxCollider>(chopper, 32, 32);

    const auto radar = registry.create();
    registry.emplace<UI_Tag>(radar);
    registry.emplace<Transform>(radar, glm::vec2(WINDOWWIDTH - 74, 10.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Sprite>(radar, "radar-image", 64, 64, 100, true);
    registry.emplace<Animation>(radar, 8, 5, true);

    const auto tank = registry.create();
    registry.emplace<Enemy_Tag>(tank);
    registry.emplace<StayOnMap_Tag>(tank);
    registry.emplace<Transform>(tank, glm::vec2(120.0, 300.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Velocity>(tank, 30.0, 0.0);
    registry.emplace<Sprite>(tank, "tank-image", 32, 32, 2);
    registry.emplace<ProjectileEmitter>(tank, glm::vec2(100.0, 0.0), 1000, 10000, 10, false);
    registry.emplace<Health>(tank, 100);
    registry.emplace<BoxCollider>(tank, 32, 32);

    const auto truck = registry.create();
    registry.emplace<Enemy_Tag>(truck);
    registry.emplace<StayOnMap_Tag>(truck);
    registry.emplace<Transform>(truck, glm::vec2(300.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Velocity>(truck, 20.0, 0.0);
    registry.emplace<Sprite>(truck, "truck-image", 32, 32, 2);
    registry.emplace<ProjectileEmitter>(truck, glm::vec2(100.0, -100.0), 2000, 10000, 10, false);
    registry.emplace<Health>(truck, 100);
    registry.emplace<BoxCollider>(truck, 32, 32);

    const auto treeA = registry.create();
    registry.emplace<Obstacle_Tag>(treeA);
    registry.emplace<Transform>(treeA, glm::vec2(200.0, 345.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Sprite>(treeA, "tree-image", 16, 32, 1);
    registry.emplace<BoxCollider>(treeA, 16, 32);

    const auto treeB = registry.create();
    registry.emplace<Obstacle_Tag>(treeB);
    registry.emplace<Transform>(treeB, glm::vec2(400.0, 345.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Sprite>(treeB, "tree-image", 16, 32, 1);
    registry.emplace<BoxCollider>(treeB, 16, 32);

    const auto label = registry.create();
    registry.emplace<UI_Tag>(label);
    SDL_Color green = {30, 200, 30};
    registry.emplace<TextLabel>(label, glm::vec2(WINDOWWIDTH / 2 - 40, 10), "Chopper 1.0", "charriot-font", green, true);

}

void Game::Setup()
{
    LoadLevel(1);
    keyPressedEventListener.connect<&KeyBoardControlSystem::OnKeyPressed>();
    keyPressedEventListener.connect<&ProjectileEmitSystem::OnKeyPressed>();
    CollisionEventListener.connect<&DamageSystem::OnCollision>();
    CollisionEventListener.connect<&MovementSystem::OnCollision>();
}

void Game::Update()
{

    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }

    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

    millisecsPreviousFrame = SDL_GetTicks();


    // Update systems
    MovementSystem::Update(registry, deltaTime);
    AnimationSystem::Update(registry);
    CameraMovementSystem::Update(registry, camera);
    ProjectileEmitSystem::Update(registry);
    ProjectileLifeCycleSystem::Update(registry);
    CollisionSystem::Update(registry);

    // Kill entities that are queued for death
    while (!Game::entitiesToKill.empty())
    {
        entt::entity entity = Game::entitiesToKill.front();
        Game::entitiesToKill.pop_front();
        registry.destroy(entity);
        Logger::Info("Entity Destroyed");
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    RenderSystem::Update(registry, renderer, assetStore, camera);
    RenderHealthSystem::Update(registry, renderer, assetStore, camera);
    RenderTextSystem::Update(registry, renderer, assetStore, camera);

    if (debugMode)
    {
        RenderColliderSystem::Update(registry, renderer, camera);
    }
    SDL_RenderPresent(renderer);
}

void Game::Run()
{
    Setup();
    while (isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
