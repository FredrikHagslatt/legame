#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entt/entt.hpp"
#include "Logger/Logger.h"
#include "Types.h"

#include "Scenes/Hub.h"
#include "Scenes/Garden.h"

#include "Events/KeyPressedEvent.h"
#include "Systems/KeyboardControlSystem.h"

int Game::mapWidth;
int Game::mapHeight;
std::list<entt::entity> Game::entitiesToKill;
entt::dispatcher Game::dispatcher;

Game::Game()
{
    mapWidth = 0;
    mapHeight = 0;
    isRunning = false;
    Logger::Info("Game Created.");
    m_registry = std::make_shared<entt::registry>();
    m_assetStore = std::make_shared<AssetStore>();
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

    m_window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOWWIDTH,
        WINDOWHEIGHT,
        SDL_WINDOW_BORDERLESS);
    if (!m_window)
    {
        Logger::Fatal("Error creating SDL window.");
        return;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer)
    {
        Logger::Fatal("Error creating SDL renderer.");
    }

    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;
    Game::dispatcher = entt::dispatcher{};
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
            Game::dispatcher.trigger(KeyPressedEvent{m_registry, sdlEvent.key.keysym.sym});
            break;
        }
    }
}

void Game::Setup()
{
    // m_sceneManager.AddScene("MENU", new MenuRoot(m_sceneManager));
    m_sceneManager.AddScene("HUB", new Hub(m_sceneManager, m_renderer, m_registry, m_assetStore));
    m_sceneManager.AddScene("GARDEN", new Garden(m_sceneManager, m_renderer, m_registry, m_assetStore));

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
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
