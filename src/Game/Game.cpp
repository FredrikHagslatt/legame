#include "Game.h"

Game::Game()
{
    isRunning = false;
    registry = std::make_unique<Registry>();
    Logger::Log("Game Created!");

}

Game::~Game()
{
    Logger::Log("Game Destroyed!");
}

void Game::Initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Err("Error initializing SDL.");
        return;
    }

    //    SDL_DisplayMode displayMode;
    //    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = 1920;  // displayMode.w;
    windowHeight = 1080; // displayMode.h;

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        Logger::Err("Error creating SDL window.");
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        Logger::Err("Error creating SDL renderer.");
    }

    //    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

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
            break;
        }
    }
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup()
{
    //TODO:
    Entity tank = registry->CreateEntity();
    Entity truck = registry->CreateEntity();



    tank.AddComponent<TransformComponent>(glm::vec2(10.0, 30.0), glm::vec2(1, 1), 0.0);
    tank.AddComponent<RigidBodyComponent>(glm::vec2(10, 50));

    tank.RemoveComponent<RigidBodyComponent>();

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

    //TODO:
    //MovementSystem.Update();
    //CollisionSystem.Update();
    //DamageSystem.Update();

}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    //TODO: Render game objects...

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