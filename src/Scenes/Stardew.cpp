#include "Scenes/Stardew.h"
#include <fstream>

extern entt::registry registry;
void Stardew::Update(double elapsedTime)
{
    // Update systems
    MovementSystem::Update(elapsedTime);
    AnimationSystem::Update();
    CameraMovementSystem::Update(camera);
    ProjectileEmitSystem::Update();
    ProjectileLifeCycleSystem::Update();
    CollisionSystem::Update();

    /*
        MovementSystem::Update(registry, elapsedTime);
        AnimationSystem::Update(registry);
        CameraMovementSystem::Update(registry, camera);
        ProjectileEmitSystem::Update(registry);
        ProjectileLifeCycleSystem::Update(registry);
        CollisionSystem::Update(registry);
    */

    UpdateScene(elapsedTime);

    // Kill entities that are queued for death
    while (!entitiesToKill.empty())
    {
        entt::entity entity = entitiesToKill.front();
        entitiesToKill.pop_front();
        registry.destroy(entity);
        Logger::Info("Entity Destroyed");
    }
}

void Stardew::RenderGraphics(double elapsedTime)
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    RenderSystem::Update(camera);
    RenderHealthSystem::Update(camera);
    RenderTextSystem::Update(camera);
    /*
        RenderSystem::Update(registry, renderer, assetStore, camera);
        RenderHealthSystem::Update(registry, renderer, assetStore, camera);
        RenderTextSystem::Update(registry, renderer, assetStore, camera);
    */

    if (debugMode)
    {
        RenderColliderSystem::Update(camera);
        //        RenderColliderSystem::Update(registry, renderer, camera);
    }
    SDL_RenderPresent(renderer);
}

void Stardew::LoadMap(std::string spritesheet, std::string map)
{
    assetStore.AddTexture(renderer, spritesheet, spritesheet);

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
                Logger::Fatal("Map is fucked! Row length not matching");
            }
        }
        mapNumRows++;
    }

    mapFile.clear();
    mapFile.seekg(0); // Go to start of file again.

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

            const auto tile = registry.create();
            registry.emplace<Transform>(tile, glm::vec2(x * (SCALE * TILESIZE) + offset.x, y * (SCALE * TILESIZE) + offset.y), glm::vec2(SCALE, SCALE), 0.0);
            registry.emplace<Sprite>(tile, spritesheet, TILESIZE, TILESIZE, 0, false, srcRectX, srcRectY);
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

    //    keyPressedEventListener.connect<&KeyBoardControlSystem::OnKeyPressed>();
    //    keyPressedEventListener.connect<&ProjectileEmitSystem::OnKeyPressed>();
    //    collisionEventListener.connect<&DamageSystem::OnCollision>();
    //    collisionEventListener.connect<&MovementSystem::OnCollision>();

    LoadScene();
}

void Stardew::Unload()
{
    UnloadScene();
}

Stardew::Stardew(SceneManager &sceneManager)
    : Scene(sceneManager)
{
}