#include "Scenes/Stardew.h"
#include <fstream>
#include "Game/Game.h"
#include "Logger/Logger.h"

void Stardew::ToggleDebugMode(const KeyPressedEvent &event)
{
    if (event.key == SDLK_d)
    {
        debugMode = !debugMode;
        if (debugMode)
        {
            Logger::Info("Debugmode activated");
        }
        else
        {
            Logger::Info("Debugmode deactivated");
        }
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
    CollisionSystem::Update(m_registry);

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

    vec2f offset(0.0);
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
            m_registry->emplace<Tile_Tag>(tile);
            m_registry->emplace<Transform>(tile, vec2f(x * (SCALE * TILESIZE) + offset.x, y * (SCALE * TILESIZE) + offset.y), vec2f(SCALE, SCALE), 0.0);
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

    auto view = m_registry->view<Player_Tag>();
    if (view.empty())
    {
        Logger::Info("Creating player");
        const auto player = m_registry->create();
        m_registry->emplace<Player_Tag>(player);
        m_registry->emplace<StayOnMap_Tag>(player);
        m_registry->emplace<Transform>(player, vec2f(200.0, 400.0), vec2f(SCALE, SCALE), 0.0);
        m_registry->emplace<Velocity>(player, 0.0, 0.0);
        m_registry->emplace<Sprite>(player, "spike-image", 16, 32, 10);
        m_registry->emplace<Animation>(player, 5, 5, true);
        m_registry->emplace<KeyboardControlled>(player, vec2f(0, -300), vec2f(300, 0), vec2f(0, 300), vec2f(-300, 0));
        m_registry->emplace<ProjectileEmitter>(player, vec2f(600.0, 600.0), 0, 10000, 10, true);
        m_registry->emplace<Health>(player, 100);
        m_registry->emplace<BoxCollider>(player, 16, 32);
    }
    else
    {
        Logger::Info("Player already exists. Not creating");
    }

    Game::dispatcher.sink<KeyPressedEvent>().connect<&KeyboardControlSystem::OnKeyPressed>();
    Game::dispatcher.sink<KeyPressedEvent>().connect<&ProjectileEmitSystem::OnKeyPressed>();
    Game::dispatcher.sink<KeyPressedEvent>().connect<&Stardew::ToggleDebugMode>(this);
    Game::dispatcher.sink<CollisionEvent>().connect<&DamageSystem::OnCollision>();
    Game::dispatcher.sink<CollisionEvent>().connect<&MovementSystem::OnCollision>();
    Game::dispatcher.sink<SceneSwitchEvent>().connect<&SceneManager::OnSceneSwitchEvent>(m_sceneManager);

    Logger::Info("[Stardew] Connecting eventlisteners");

    LoadScene();
}

void Stardew::Unload()
{
    Game::dispatcher.sink<KeyPressedEvent>().disconnect<&KeyboardControlSystem::OnKeyPressed>();
    Game::dispatcher.sink<KeyPressedEvent>().disconnect<&ProjectileEmitSystem::OnKeyPressed>();
    Game::dispatcher.sink<KeyPressedEvent>().disconnect<&Stardew::ToggleDebugMode>(this);
    Game::dispatcher.sink<CollisionEvent>().disconnect<&DamageSystem::OnCollision>();
    Game::dispatcher.sink<CollisionEvent>().disconnect<&MovementSystem::OnCollision>();
    Game::dispatcher.sink<SceneSwitchEvent>().disconnect<&SceneManager::OnSceneSwitchEvent>(m_sceneManager);
    Logger::Info("[Stardew] Disconnecting eventlisteners");

    auto projectiles = m_registry->view<Projectile_Tag>();
    m_registry->destroy(projectiles.begin(), projectiles.end());

    auto enemies = m_registry->view<Enemy_Tag>();
    m_registry->destroy(enemies.begin(), enemies.end());

    auto obstacles = m_registry->view<Obstacle_Tag>();
    m_registry->destroy(obstacles.begin(), obstacles.end());

    auto tiles = m_registry->view<Tile_Tag>();
    m_registry->destroy(tiles.begin(), tiles.end());

    auto labels = m_registry->view<TextLabel>();
    m_registry->destroy(labels.begin(), labels.end());

    UnloadScene();
}

Stardew::Stardew(SceneManager &sceneManager, SDL_Renderer *renderer, std::shared_ptr<entt::registry> registry, std::shared_ptr<AssetStore> assetStore)
    : Scene(sceneManager, renderer, registry, assetStore)
{
}