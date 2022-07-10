#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entt/entt.hpp"
#include "Logger/Logger.h"
#include "Types.h"

#include "Scenes/Hub.h"
#include "Scenes/Garden.h"
#include "Scenes/Menu/MenuRoot.h"

#include "Events/EventDispatcher.h"
#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"

int Game::mapWidth;
int Game::mapHeight;
std::list<entt::entity> Game::entitiesToKill;
entt::dispatcher Event::dispatcher;

Game::Game()
    : m_sceneManager(SceneManager("Game")),
      m_registry(std::make_shared<entt::registry>()),
      m_assetStore(std::make_shared<AssetStore>())
{
    mapWidth = 0;
    mapHeight = 0;
    isRunning = false;
    Logger::Info("[Game] Game Created.");
}

Game::~Game()
{
    Logger::Info("[Game] Game Destroyed.");
}

void Game::Initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Fatal("[Game] Error initializing SDL.");
        return;
    }

    if (TTF_Init() != 0)
    {
        Logger::Fatal("[Game] Error initializing TTF.");
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
        Logger::Fatal("[Game] Error creating SDL window.");
        return;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer)
    {
        Logger::Fatal("[Game] Error creating SDL renderer.");
    }

    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;
    Event::dispatcher = entt::dispatcher{};
    Logger::Info("[Game] SDL Initialized.");
}

void Game::ProcessInput()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        SDL_Keycode keycode = sdlEvent.key.keysym.sym;
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (keycode == SDLK_ESCAPE)
            {
                isRunning = false;
            }
            Event::dispatcher.trigger(KeyPressedEvent{m_registry, keycode});
            break;
        case SDL_KEYUP:
            Event::dispatcher.trigger(KeyReleasedEvent{m_registry, keycode});
        }
    }
}

void Game::Setup()
{
    m_sceneManager.AddScene("Hub", std::make_shared<Hub>(m_renderer, m_registry, m_assetStore));
    m_sceneManager.AddScene("Garden", std::make_shared<Garden>(m_renderer, m_registry, m_assetStore));
    m_sceneManager.AddScene("MenuRoot", std::make_shared<MenuRoot>(m_renderer, m_registry, m_assetStore));

    // m_sceneManager.AddScene("GRASS", new StardewTemplate(m_sceneManager));
    // m_sceneManager.AddScene("MAPEDITOR", new MapEditor(m_sceneManager));
    // sceneManager->AddScene(CREDITS, new CreditsScene(sceneManager));
    m_sceneManager.QueueSceneChange("MenuRoot");

    Event::dispatcher.sink<SceneSwitchEvent>().connect<&SceneManager::OnSceneSwitchEvent>(m_sceneManager);
    Logger::Info("[Game] Game Setup.");
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
