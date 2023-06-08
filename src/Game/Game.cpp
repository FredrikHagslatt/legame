#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entt/entt.hpp"
#include "Logger/Logger.h"
#include "DevTools/DevTools.h"
#include "Types.h"

// #include "Scenes/Hub.h"
// #include "Scenes/Garden.h"
#include "Scenes/GenericTopDown.h"
#include "Scenes/Menu/MenuRoot.h"
#include "Scenes/MapEditor.h"

#include "Events/EventDispatcher.h"
#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"

#include "Events/MouseMotionEvent.h"
#include "Events/MouseButtonPressedEvent.h"
#include "Events/MouseButtonReleasedEvent.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_sdlrenderer.h>

std::list<entt::entity> Game::entitiesToKill;
entt::dispatcher Event::dispatcher;

Game::Game()
    : m_sceneManager(SceneManager("Game")),
      m_registry(std::make_shared<entt::registry>()),
      m_assetStore(std::make_shared<AssetStore>())
{
    isRunning = false;
    Logger::Info("[Game] Game Created.");
    //    m_entityExplorer = EntityExplorer();
}

Game::~Game()
{
    Logger::Info("[Game] Game Destroyed.");
}

void Game::Initialize()
{

    SDL_version linked;
    SDL_GetVersion(&linked);
    Logger::Info("[Game] Linking against SDL version: " + std::to_string(linked.major) + "." + std::to_string(linked.minor) + "." + std::to_string(linked.patch));

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Error("[Game] Error initializing SDL.");
        return;
    }

    if (TTF_Init() != 0)
    {
        Logger::Error("[Game] Error initializing TTF.");
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
        Logger::Error("[Game] Error creating SDL window.");
        return;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer)
    {
        Logger::Error("[Game] Error creating SDL renderer.");
    }

    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    Event::dispatcher = entt::dispatcher{};
    Logger::Info("[Game] SDL Initialized.");

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer_Init(m_renderer);
    Logger::Info("[Game] ImGui Initialized.");

    isRunning = true;
}

void Game::ProcessInput()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        // Handle ImGui SDL input
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);

        SDL_Keycode keycode = sdlEvent.key.keysym.sym;
        // Handle Game SDL input
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
            break;
        case SDL_MOUSEMOTION:
            Event::dispatcher.trigger(MouseMotionEvent{sdlEvent.motion});
            break;
        case SDL_MOUSEBUTTONDOWN:
            Event::dispatcher.trigger(MouseButtonPressedEvent{sdlEvent.button});
            break;
        case SDL_MOUSEBUTTONUP:
            Event::dispatcher.trigger(MouseButtonReleasedEvent{sdlEvent.button});
            break;
        }
    }
}

void Game::Setup()
{
    SDL_ShowCursor(SDL_DISABLE);

    m_sceneManager.AddScene("MenuRoot", std::make_shared<MenuRoot>(m_renderer, m_registry, m_assetStore));
    m_sceneManager.AddScene("GenericTopDown", std::make_shared<GenericTopDown>(m_renderer, m_registry, m_assetStore));

    // m_sceneManager.AddScene("CREDITS", ...);

    m_sceneManager.QueueSceneChange("MenuRoot", "-");

    m_sceneManager.AddScene("MapEditor", std::make_shared<MapEditor>(m_renderer, m_registry, m_assetStore));

    Event::dispatcher.sink<SceneSwitchEvent>().connect<&SceneManager::OnSceneSwitchEvent>(m_sceneManager);
    Event::dispatcher.sink<KeyPressedEvent>().connect<&DevTools::ToggleShowDevTools>();
    Logger::Info("[Game] Game Setup.");
}

double Game::HandleFramerate()
{
    if (!MAX_FPS_UNLOCKED)
    {
        int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
        if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
        {
            SDL_Delay(timeToWait);
        }
    }

    double elapsedTime = static_cast<double>(SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
    millisecsPreviousFrame = SDL_GetTicks();
    return elapsedTime;
}

void Game::KillQueuedEntities()
{
    if (!entitiesToKill.empty())
    {
        Logger::Info("Killing entities that are queued for death ");
    }

    while (!entitiesToKill.empty())
    {
        entt::entity entity = entitiesToKill.front();
        entitiesToKill.pop_front();
        if (m_registry->valid(entity))
        {
            m_registry->destroy(entity);
        }
    }
}

void Game::Update()
{
    double elapsedTime = HandleFramerate();

    m_sceneManager.Update(elapsedTime);

    SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
    SDL_RenderClear(m_renderer);

    m_sceneManager.RenderGraphics(elapsedTime);

    if (DevTools::showDevTools)
    {
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        DevTools::Render(elapsedTime);

        if (DevTools::showEntityExplorer)
        {
            m_entityExplorer.Render();
        }
        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    }

    SDL_RenderPresent(m_renderer);

    KillQueuedEntities();
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
    // Destroy ImGui
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // Destroy SDL
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
