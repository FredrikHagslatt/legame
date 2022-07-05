#include "Scenes/Stardew.h"
#include <fstream>
#include "Game/Game.h"

void Stardew::ToggleDebugMode(const KeyPressedEvent &event)
{
    if (event.key == SDLK_d)
    {
        debugMode = !debugMode;
    }
}

void Stardew::Update(double elapsedTime)
{
    // Update systems
    MovementSystem::Update(m_registry, elapsedTime);
    AnimationSystem::Update(m_registry);
    CameraMovementSystem::Update(m_registry, camera);
    ProjectileEmitSystem::Update(m_registry);
    ProjectileLifeCycleSystem::Update(m_registry);
    CollisionSystem::Update(m_registry, m_dispatcher);

    UpdateScene(elapsedTime);

    // Kill entities that are queued for death
    while (!Game::entitiesToKill.empty())
    {
        entt::entity entity = Game::entitiesToKill.front();
        Game::entitiesToKill.pop_front();
        m_registry->destroy(entity);
        Logger::Info("Queued entity destroyed");
    }
}

void Stardew::RenderGraphics(double elapsedTime)
{
    SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
    SDL_RenderClear(m_renderer);

    RenderSystem::Update(m_registry, m_renderer, m_assetStore, camera);
    RenderHealthSystem::Update(m_registry, m_renderer, m_assetStore, camera);
    RenderTextSystem::Update(m_registry, m_renderer, m_assetStore, camera);

    if (debugMode)
    {
        RenderColliderSystem::Update(m_registry, m_renderer, camera);
    }

    RenderScene(elapsedTime);
    SDL_RenderPresent(m_renderer);
}

void Stardew::LoadMap(std::string spritesheet, std::string map)
{
    m_assetStore->AddTexture(m_renderer, spritesheet, spritesheet);

    int mapNumCols = 0;
    int mapNumRows = 0;

    std::fstream mapFile;
    mapFile.open(map);

    // Get map dimensions
    std::string line;
    while (std::getline(mapFile, line))
    {
        if (mapNumCols == 0)
        {
            mapNumCols = (line.size() + 1) / 3;
        }
        else
        {
            if (mapNumCols != (line.size() + 1) / 3)
            {
                Logger::Fatal("[Stardew] Map is fucked! Row length not matching");
            }
        }
        mapNumRows++;
    }

    mapFile.clear();
    mapFile.seekg(0); // Go to start of file again.

    Logger::Info("[Stardew] Mapsize: " + std::to_string(mapNumCols) + " x " + std::to_string(mapNumRows));

    Game::mapWidth = mapNumCols * TILESIZE * SCALE;
    Game::mapHeight = mapNumRows * TILESIZE * SCALE;

    glm::vec2 offset;
    if (Game::mapWidth < WINDOWWIDTH)
    {
        offset.x = (WINDOWWIDTH - Game::mapWidth) / 2;
    }
    if (Game::mapHeight < WINDOWHEIGHT)
    {
        offset.y = (WINDOWHEIGHT - Game::mapHeight) / 2;
    }

    // Read map, create tiles.
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

            const auto tile = m_registry->create();
            m_registry->emplace<Transform>(tile, glm::vec2(x * (SCALE * TILESIZE) + offset.x, y * (SCALE * TILESIZE) + offset.y), glm::vec2(SCALE, SCALE), 0.0);
            m_registry->emplace<Sprite>(tile, spritesheet, TILESIZE, TILESIZE, 0, false, srcRectX, srcRectY);
        }
    }
    mapFile.close();
}

void Stardew::Load()
{
    camera.x = 0;
    camera.y = 0;
    camera.w = WINDOWWIDTH;
    camera.h = WINDOWHEIGHT;

    m_dispatcher.sink<KeyPressedEvent>().connect<&KeyboardControlSystem::OnKeyPressed>();
    m_dispatcher.sink<KeyPressedEvent>().connect<&ProjectileEmitSystem::OnKeyPressed>();
    m_dispatcher.sink<KeyPressedEvent>().connect<&Stardew::ToggleDebugMode>(this);
    m_dispatcher.sink<CollisionEvent>().connect<&DamageSystem::OnCollision>();
    m_dispatcher.sink<CollisionEvent>().connect<&MovementSystem::OnCollision>();
    Logger::Info("[Stardew] Connecting eventlisteners");

    LoadScene();
}

void Stardew::Unload()
{
    m_dispatcher.sink<KeyPressedEvent>().disconnect<&KeyboardControlSystem::OnKeyPressed>();
    m_dispatcher.sink<KeyPressedEvent>().disconnect<&ProjectileEmitSystem::OnKeyPressed>();
    m_dispatcher.sink<KeyPressedEvent>().disconnect<&Stardew::ToggleDebugMode>(this);
    m_dispatcher.sink<CollisionEvent>().disconnect<&DamageSystem::OnCollision>();
    m_dispatcher.sink<CollisionEvent>().disconnect<&MovementSystem::OnCollision>();
    Logger::Info("[Stardew] Disconnecting eventlisteners");

    UnloadScene();
}

Stardew::Stardew(SceneManager &sceneManager, SDL_Renderer *renderer, std::shared_ptr<entt::registry> registry, std::shared_ptr<AssetStore> assetStore, entt::dispatcher &dispatcher)
    : Scene(sceneManager, renderer, registry, assetStore, dispatcher)
{
}