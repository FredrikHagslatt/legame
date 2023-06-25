#include "Scenes/TopDown.h"
#include <fstream>
#include "Events/EventDispatcher.h"
#include "Logger/Logger.h"
#include "DevTools/DevTools.h"

void TopDown::Update(const double elapsedTime)
{
    // Update systems
    LifeTimeSystem::Update(m_registry);
    MovementSystem::Update(m_registry, elapsedTime, m_mapWidth, m_mapHeight);
    AnimationSystem::Update(m_registry);
    CameraMovementSystem::Update(m_registry, m_camera, m_mapWidth, m_mapHeight);
    ProjectileEmitSystem::Update(m_registry);
    ProjectileLifeCycleSystem::Update(m_registry);
    CollisionSystem::Update(m_registry);
    CrosshairSystem::Update(m_registry, m_camera);
    SpellSystem::Update(m_registry, elapsedTime);

    UpdateScene(elapsedTime);
}

void TopDown::RenderGraphics(const double elapsedTime)
{
    RenderTileMapSystem::Update(m_tileMap, m_renderer, m_assetStore, m_camera);
    RenderSystem::Update(m_registry, m_renderer, m_assetStore, m_camera);
    RenderHealthSystem::Update(m_registry, m_renderer, m_assetStore, m_camera);
    RenderTextSystem::Update(m_registry, m_renderer, m_assetStore, m_camera);

    if (DevTools::renderHitboxes)
    {
        RenderColliderSystem::Update(m_registry, m_renderer, m_camera);
    }

    RenderScene(elapsedTime);
}

void TopDown::LoadMap(std::string spritesheet, std::string map)
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
                Logger::Error("[TopDown] Map is fucked! Row length not matching");
            }
        }
        mapNumRows++;
    }

    mapFile.clear();
    mapFile.seekg(0); // Go to start of file again.

    Logger::Info("[TopDown] Mapsize: " + std::to_string(mapNumCols) + " x " + std::to_string(mapNumRows));

    m_mapWidth = mapNumCols * TILESIZE * SCALE;
    m_mapHeight = mapNumRows * TILESIZE * SCALE;

    // Read map, create tiles.
    for (int y = 0; y < mapNumRows; y++)
    {
        m_tileMap.push_back(std::vector<Sprite>{});
        for (int x = 0; x < mapNumCols; x++)
        {
            char ch;
            mapFile.get(ch);

            int srcRectY = std::atoi(&ch) * TILESIZE;
            mapFile.get(ch);
            int srcRectX = std::atoi(&ch) * TILESIZE;
            mapFile.ignore();

            m_tileMap.at(y).push_back(Sprite(spritesheet, TILESIZE, TILESIZE, 0, false, srcRectX, srcRectY));
        }
    }
    mapFile.close();
}

void TopDown::Load(std::string level)
{
    m_camera.x = 0;
    m_camera.y = 0;
    m_camera.w = WINDOWWIDTH;
    m_camera.h = WINDOWHEIGHT * 4 / 5;

    auto playerCheckView = m_registry->view<Player_Tag>();
    if (playerCheckView.empty())
    {
        m_assetStore->AddTexture(m_renderer, "spike-image", "assets/images/characters/friend/Spike.png");
        Logger::Info("[TopDown] Creating player");
        const auto player = m_registry->create();
        m_registry->emplace<Player_Tag>(player);
        m_registry->emplace<StayOnMap_Tag>(player);
        m_registry->emplace<KeyboardControlled_Tag>(player);
        m_registry->emplace<Transform>(player, vec2f(200.0, 500.0));
        m_registry->emplace<Velocity>(player, 300.0, vec2f(0), vec2f(0.0, 1.0));
        m_registry->emplace<Sprite>(player, "spike-image", 16, 32, 26);
        m_registry->emplace<Animation>(player, 5, 5, true, true);
        m_registry->emplace<ProjectileEmitter>(player, 600.0, vec2f(1.0, 1.0), 0, 10000, 10, true, true);
        m_registry->emplace<Health>(player, 100);
        m_registry->emplace<CircleCollider>(player, 6, vec2f(8, 32 - 6));
    }
    else
    {
        Logger::Info("[TopDown] Player already exists. Not creating");
    }

    auto crosshairCheckView = m_registry->view<Crosshair_Tag>();
    if (crosshairCheckView.empty())
    {
        m_assetStore->AddTexture(m_renderer, "crosshair", "assets/images/user-interface/crosshair/crosshair1.png");
        Logger::Info("[TopDown] Creating crosshair");
        const auto crosshair = m_registry->create();
        m_registry->emplace<Crosshair_Tag>(crosshair);
        m_registry->emplace<UI_Tag>(crosshair);
        m_registry->emplace<Transform>(crosshair, vec2f(250.0, 500.0));
        m_registry->emplace<Sprite>(crosshair, "crosshair", 7, 7);
    }
    else
    {
        Logger::Info("[TopDown] Crosshair already exists. Not creating");
    }

    m_assetStore->AddTexture(m_renderer, "blinkSmoke-image", "assets/images/spells/blinkSmoke.png");
    m_assetStore->AddTexture(m_renderer, "bullet-image", "assets/images/bullet.png");
    m_assetStore->AddTexture(m_renderer, "fireball-spritesheet", "assets/images/spells/fireball-spritesheet.png");
    m_assetStore->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
    m_assetStore->AddFont("pico8-font-5", "assets/fonts/pico8.ttf", 5);

    m_assetStore->AddTexture(m_renderer, "user-interface", "assets/images/user-interface/topdown-ui.png");
    const auto user_interface = m_registry->create();
    m_registry->emplace<Transform>(user_interface, vec2f(0.0, 576.0));
    m_registry->emplace<Sprite>(user_interface, "user-interface", 400, 48, 0, true);
    m_registry->emplace<UI_Tag>(user_interface);

    m_assetStore->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
    const auto label = m_registry->create();
    m_registry->emplace<UI_Tag>(label);
    SDL_Color black = {0, 0, 0};
    m_registry->emplace<TextLabel>(label, vec2f(WINDOWWIDTH / 2 - 100, WINDOWHEIGHT - 70), "User interface placeholder", "charriot-font", black, true);

    Event::dispatcher.sink<KeyPressedEvent>().connect<&KeyboardControlSystem::OnKeyPressed>();
    Event::dispatcher.sink<KeyReleasedEvent>().connect<&KeyboardControlSystem::OnKeyReleased>();
    Event::dispatcher.sink<KeyPressedEvent>().connect<&ProjectileEmitSystem::OnKeyPressed>();
    Event::dispatcher.sink<KeyPressedEvent>().connect<&SpellSystem::OnKeyPressed>(m_registry);
    Event::dispatcher.sink<MouseButtonPressedEvent>().connect<&ProjectileEmitSystem::OnMouseButtonPressed>(m_projectileEmitSystemData);
    Event::dispatcher.sink<CollisionEvent>().connect<&DamageSystem::OnCollision>();
    Event::dispatcher.sink<CollisionEvent>().connect<&MovementSystem::OnCollision>();
    Event::dispatcher.sink<CollisionEvent>().connect<&TriggerSystem::OnCollision>();
    Logger::Info("[TopDown] Connecting eventlisteners");

    LoadScene(level);
}

void TopDown::Unload()
{
    Event::dispatcher.sink<KeyPressedEvent>().disconnect<&KeyboardControlSystem::OnKeyPressed>();
    Event::dispatcher.sink<KeyReleasedEvent>().disconnect<&KeyboardControlSystem::OnKeyReleased>();
    Event::dispatcher.sink<KeyPressedEvent>().disconnect<&ProjectileEmitSystem::OnKeyPressed>();
    Event::dispatcher.sink<KeyPressedEvent>().disconnect<&SpellSystem::OnKeyPressed>(m_registry);
    Event::dispatcher.sink<MouseButtonPressedEvent>().disconnect<&ProjectileEmitSystem::OnMouseButtonPressed>(m_projectileEmitSystemData);
    Event::dispatcher.sink<CollisionEvent>().disconnect<&DamageSystem::OnCollision>();
    Event::dispatcher.sink<CollisionEvent>().disconnect<&MovementSystem::OnCollision>();
    Event::dispatcher.sink<CollisionEvent>().disconnect<&TriggerSystem::OnCollision>();
    Logger::Info("[TopDown] Disconnecting eventlisteners");

    m_tileMap.clear();

    auto projectiles = m_registry->view<Projectile_Tag>();
    m_registry->destroy(projectiles.begin(), projectiles.end());

    auto enemies = m_registry->view<Enemy_Tag>();
    m_registry->destroy(enemies.begin(), enemies.end());

    auto obstacles = m_registry->view<Obstacle_Tag>();
    m_registry->destroy(obstacles.begin(), obstacles.end());

    auto triggers = m_registry->view<Trigger_Tag>();
    m_registry->destroy(triggers.begin(), triggers.end());

    auto labels = m_registry->view<TextLabel>();
    m_registry->destroy(labels.begin(), labels.end());

    auto UIs = m_registry->view<UI_Tag>();
    m_registry->destroy(UIs.begin(), UIs.end());

    Logger::Info("[TopDown] Destroying entities");

    UnloadScene();
}

TopDown::TopDown(SDL_Renderer *renderer, std::shared_ptr<entt::registry> registry, std::shared_ptr<AssetStore> assetStore)
    : Scene(renderer, registry, assetStore)
{
}