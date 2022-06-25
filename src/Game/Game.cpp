#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>

#include "entt/entt.hpp"
#include "Logger/Logger.h"
#include <glm/glm.hpp>

#include "Components/Transform.h"
#include "Components/Velocity.h"
#include "Components/Sprite.h"
#include "Components/Animation.h"
#include "Components/BoxCollider.h"
#include "Components/KeyboardControlled.h"
#include "Components/MainPlayer.h"
#include "Components/ProjectileEmitter.h"
#include "Components/Health.h"
#include "Components/TextLabel.h"

#include "Systems/RenderSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/KeyboardControlSystem.h"

/*
#include "Systems/RenderColliderSystem.h"
#include "Systems/RenderTextSystem.h"
#include "Systems/RenderHealthSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/DamageSystem.h"
#include "Systems/CameraMovementSystem.h"
#include "Systems/ProjectileEmitSystem.h"
#include "Systems/ProjectileLifecycleSystem.h"
*/

#include "Events/KeyPressedEvent.h"

int Game::windowWidth;
int Game::windowHeight;
int Game::mapWidth;
int Game::mapHeight;

Game::Game()
{
    isRunning = false;
    assetStore = std::make_unique<AssetStore>();
    eventBus = std::make_unique<EventBus>();
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

    windowWidth = 800;  // displayMode.w;
    windowHeight = 600; // displayMode.h;

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
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
    camera.w = windowWidth;
    camera.h = windowHeight;

    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
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
                else{
                    Logger::Info("Debug mode dectivated");
                }
            }
            eventBus->EmitEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);
            break;
        }
    }
}

void Game::LoadLevel(int level)
{
    /*
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<AnimationSystem>();
    registry->AddSystem<CollisionSystem>();
    registry->AddSystem<RenderColliderSystem>();
    registry->AddSystem<DamageSystem>();
    registry->AddSystem<KeyboardControlSystem>();
    registry->AddSystem<CameraMovementSystem>();
    registry->AddSystem<ProjectileEmitSystem>();
    registry->AddSystem<ProjectileLifecycleSystem>();
    registry->AddSystem<RenderTextSystem>();
    registry->AddSystem<RenderHealthSystem>();
    */

    assetStore->AddTexture(renderer, "tilemap-image", "assets/tilemaps/jungle.png");
    assetStore->AddTexture(renderer, "tank-image", "assets/images/tank-panther-right.png");
    assetStore->AddTexture(renderer, "truck-image", "assets/images/truck-ford-right.png");
    assetStore->AddTexture(renderer, "tree-image", "assets/images/tree.png");
    assetStore->AddTexture(renderer, "chopper-image", "assets/images/chopper-spritesheet.png");
    assetStore->AddTexture(renderer, "radar-image", "assets/images/radar.png");
    assetStore->AddTexture(renderer, "bullet-image", "assets/images/bullet.png");

    assetStore->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
    assetStore->AddFont("pico8-font-5", "assets/fonts/pico8.ttf", 5);
    assetStore->AddFont("pico8-font-10", "assets/fonts/pico8.ttf", 10);

    int tileSize = 32;
    double tileScale = 2.0;
    int mapNumCols = 25;
    int mapNumRows = 20;

    std::fstream mapFile;
    mapFile.open("assets/tilemaps/jungle.map");

    for (int y = 0; y < mapNumRows; y++)
    {
        for(int x = 0; x < mapNumCols; x++)
        {
            char ch;
            mapFile.get(ch);
            int srcRectY = std::atoi(&ch) * tileSize;
            mapFile.get(ch);
            int srcRectX = std::atoi(&ch) * tileSize;
            mapFile.ignore();

            const auto tile = registry.create();
            registry.emplace<Transform>(tile, glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
            registry.emplace<Sprite>(tile, "tilemap-image", tileSize, tileSize, 0, false, srcRectX, srcRectY);

/*
            Entity tile = registry->CreateEntity();
            tile.Group("tiles");
            tile.AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
            tile.AddComponent<SpriteComponent>("tilemap-image", tileSize, tileSize, 0, false, srcRectX, srcRectY);
*/
        }
    }

    mapFile.close();
    mapWidth = mapNumCols * tileSize * tileScale;
    mapHeight = mapNumRows * tileSize * tileScale;

/*
    Entity chopper = registry->CreateEntity();
    chopper.Tag("player");
    chopper.AddComponent<MainPlayerComponent>();
    chopper.AddComponent<TransformComponent>(glm::vec2(10.0, 50.0), glm::vec2(1.0, 1.0), 0.0);
    chopper.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
    chopper.AddComponent<SpriteComponent>("chopper-image", 32, 32, 10);
    chopper.AddComponent<AnimationComponent>(2, 12, true);
    chopper.AddComponent<BoxColliderComponent>(32, 32);
    chopper.AddComponent<ProjectileEmitterComponent>(glm::vec2(300.0, 300.0), 0, 10000, 10, true);
    chopper.AddComponent<KeyboardControlledComponent>(glm::vec2(0, -300), glm::vec2(300, 0), glm::vec2(0, 300), glm::vec2(-300, 0));
    chopper.AddComponent<HealthComponent>(100);
*/

    const auto chopper = registry.create();
    registry.emplace<Transform>(chopper, glm::vec2(100.0, 100.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Velocity>(chopper, 100.0, 0.0);
    registry.emplace<Sprite>(chopper, "chopper-image", 32, 32, 10);
    registry.emplace<Animation>(chopper, 2, 12, true);

/*
    Entity radar = registry->CreateEntity();
    radar.AddComponent<TransformComponent>(glm::vec2(windowWidth - 74, 10), glm::vec2(1.0, 1.0), 0.0);
    radar.AddComponent<SpriteComponent>("radar-image", 64, 64, 100, true);
    radar.AddComponent<AnimationComponent>(8, 5, true);
*/
    const auto radar = registry.create();
    registry.emplace<Transform>(radar, glm::vec2(windowWidth - 74, 10.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Sprite>(radar, "radar-image", 64, 64, 100, true);
    registry.emplace<Animation>(radar, 8, 5, true);

/*
    Entity tank = registry->CreateEntity();
    tank.Group("enemies");
    tank.AddComponent<TransformComponent>(glm::vec2(500.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
    tank.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
    tank.AddComponent<SpriteComponent>("tank-image", 32, 32, 2);
    tank.AddComponent<BoxColliderComponent>(32, 32);
//    tank.AddComponent<ProjectileEmitterComponent>(glm::vec2(100.0, 0.0), 1000, 1000, 10, false);
    tank.AddComponent<HealthComponent>(100);
*/

    const auto tank = registry.create();
    registry.emplace<Transform>(tank, glm::vec2(120.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Velocity>(tank, 30.0, 0.0);
    registry.emplace<Sprite>(tank, "tank-image", 32, 32, 2);

/*
    Entity truck = registry->CreateEntity();
    truck.Group("enemies");
    truck.AddComponent<TransformComponent>(glm::vec2(120.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
    truck.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
    truck.AddComponent<SpriteComponent>("truck-image", 32, 32, 1);
    truck.AddComponent<BoxColliderComponent>(32, 32);
    truck.AddComponent<ProjectileEmitterComponent>(glm::vec2(0.0, 100.0), 2000, 5000, 10, false);
    truck.AddComponent<HealthComponent>(100);
*/
    const auto truck = registry.create();
    registry.emplace<Transform>(truck, glm::vec2(300.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Velocity>(truck, 20.0, 0.0);
    registry.emplace<Sprite>(truck, "truck-image", 32, 32, 2);

/*
    Entity treeA = registry->CreateEntity();
    treeA.Group("obstacles");
    treeA.AddComponent<TransformComponent>(glm::vec2(400.0, 495.0), glm::vec2(1.0, 1.0), 0.0);
    treeA.AddComponent<SpriteComponent>("tree-image", 16, 32, 1);
    treeA.AddComponent<BoxColliderComponent>(16, 32);

    Entity treeB = registry->CreateEntity();
    treeB.Group("obstacles");
    treeB.AddComponent<TransformComponent>(glm::vec2(600.0, 495.0), glm::vec2(1.0, 1.0), 0.0);
    treeB.AddComponent<SpriteComponent>("tree-image", 16, 32, 1);
    treeB.AddComponent<BoxColliderComponent>(16, 32);

    Entity label = registry->CreateEntity();
    SDL_Color green = {0, 200, 0};
    label.AddComponent<TextLabelComponent>(glm::vec2(windowWidth / 2 - 40, 10), "Chopper 1.0", "charriot-font", green, true);
*/


}

void Game::Setup()
{
    LoadLevel(1);
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

    // Reset all event handlers for the current frame
    eventBus->Reset();

    KeyboardControlSystem::SubscribeToEvents(eventBus);
/*
    // Subscribe to events
    registry->GetSystem<MovementSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<DamageSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<ProjectileEmitSystem>().SubscribeToEvents(eventBus);
*/

    // Update systems

    MovementSystem::Update(registry, deltaTime);
    AnimationSystem::Update(registry);
/*
    registry->GetSystem<MovementSystem>().Update(deltaTime);
    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<CollisionSystem>().Update(eventBus);
    registry->GetSystem<CameraMovementSystem>().Update(camera);
    registry->GetSystem<ProjectileEmitSystem>().Update(registry);
    registry->GetSystem<ProjectileLifecycleSystem>().Update();
*/
    //registry->GetSystem<DamageSystem>().Update();
   
    //Update registry at end of frame
    //registry->Update();
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    RenderSystem::Update(registry, renderer, assetStore, camera);

/*
    registry->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);
    registry->GetSystem<RenderTextSystem>().Update(renderer, assetStore, camera);
    registry->GetSystem<RenderHealthSystem>().Update(renderer, assetStore, camera);
*/

    if(debugMode)
    {
//        registry->GetSystem<RenderColliderSystem>().Update(renderer, camera);
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