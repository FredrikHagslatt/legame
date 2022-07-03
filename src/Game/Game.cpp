#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entt/entt.hpp"
#include "Logger/Logger.h"
#include <glm/glm.hpp>
#include "Scenes/Hub.h"

extern entt::registry registry;
extern SDL_Renderer *renderer;
extern AssetStore assetStore;

Game::Game()
{
    isRunning = false;
    //    assetStore = std::make_unique<AssetStore>();

    Logger::Info("Game Created.");
}

Game::~Game()
{
    Logger::Info("Game Destroyed.");
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

    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;
    Logger::Info("SDL Initialized.");
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

            /*   --  SETUP EVENTLISTENER IN STARDEW  --
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
            */
            // KeyPressedEvent keyPressedEvent{sdlEvent.key.keysym.sym};
            // keyPressedEventEmitter.publish(keyPressedEvent);
            break;
        }
    }
}

void Game::Setup()
{

    // m_sceneManager.AddScene("MENU", new MenuRoot(m_sceneManager));
    m_sceneManager.AddScene("HUB", new Hub(m_sceneManager));
    // m_sceneManager.AddScene("GRASS", new StardewTemplate(m_sceneManager));
    // m_sceneManager.AddScene("MAPEDITOR", new MapEditor(m_sceneManager));
    // sceneManager->AddScene(CREDITS, new CreditsScene(sceneManager));
    m_sceneManager.ChangeScene("HUB");
    Logger::Info("Game Setup.");
}

double Game::ElapsedTime()
{
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }
    double elapsedTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
    millisecsPreviousFrame = SDL_GetTicks();
    return elapsedTime;
}

void Game::Update()
{
    m_sceneManager.Cycle(ElapsedTime());
}

void Game::Run()
{
    Setup();
    while (isRunning)
    {
        ProcessInput();
        Update();
    }
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
