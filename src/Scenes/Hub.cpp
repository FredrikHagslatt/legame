#include "Hub.h"
#include "Constants.h"

void Hub::UpdateScene(double elapsedTime)
{
}
void Hub::RenderScene(double elapsedTime)
{
}

void Hub::LoadScene()
{

    LoadMap("assets/tilemaps/ground_tiles.png", "assets/tilemaps/hub.map");

    m_assetStore->AddTexture(m_renderer, "tank-image", "assets/images/tank-panther-right.png");
    m_assetStore->AddTexture(m_renderer, "truck-image", "assets/images/truck-ford-right.png");
    m_assetStore->AddTexture(m_renderer, "tree-image", "assets/images/tree.png");
    m_assetStore->AddTexture(m_renderer, "chopper-image", "assets/images/chopper-spritesheet.png");
    m_assetStore->AddTexture(m_renderer, "radar-image", "assets/images/radar.png");
    m_assetStore->AddTexture(m_renderer, "bullet-image", "assets/images/bullet.png");

    m_assetStore->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
    m_assetStore->AddFont("pico8-font-5", "assets/fonts/pico8.ttf", 5);
    m_assetStore->AddFont("pico8-font-10", "assets/fonts/pico8.ttf", 10);

    const auto chopper = m_registry->create();
    m_registry->emplace<Enemy_Tag>(chopper);
    m_registry->emplace<StayOnMap_Tag>(chopper);
    m_registry->emplace<Transform>(chopper, vec2f(100.0, 100.0), vec2f(1.0, 1.0), 0.0);
    m_registry->emplace<Velocity>(chopper, 50.0, vec2f(1.0, 0));
    m_registry->emplace<Sprite>(chopper, "chopper-image", 32, 32, 10);
    m_registry->emplace<Animation>(chopper, 2, 12, true);
    m_registry->emplace<ProjectileEmitter>(chopper, 300.0, vec2f(1.0, 1.0), 0, 10000, 10);
    m_registry->emplace<Health>(chopper, 100);
    m_registry->emplace<BoxCollider>(chopper, 32, 32);

    const auto radar = m_registry->create();
    m_registry->emplace<UI_Tag>(radar);
    m_registry->emplace<Transform>(radar, vec2f(WINDOWWIDTH - 74, 10.0), vec2f(1.0, 1.0), 0.0);
    m_registry->emplace<Sprite>(radar, "radar-image", 64, 64, 100, true);
    m_registry->emplace<Animation>(radar, 8, 5, true);

    const auto tank = m_registry->create();
    m_registry->emplace<Enemy_Tag>(tank);
    m_registry->emplace<StayOnMap_Tag>(tank);
    m_registry->emplace<Transform>(tank, vec2f(120.0, 300.0), vec2f(1.0, 1.0), 0.0);
    m_registry->emplace<Velocity>(tank, 30.0, vec2f(1.0, 0.0));
    m_registry->emplace<Sprite>(tank, "tank-image", 32, 32, 2);
    m_registry->emplace<ProjectileEmitter>(tank, 100.0, vec2f(1.0, 0.0), 1000, 10000, 10);
    m_registry->emplace<Health>(tank, 100);
    m_registry->emplace<BoxCollider>(tank, 32, 32);

    const auto truck = m_registry->create();
    m_registry->emplace<Enemy_Tag>(truck);
    m_registry->emplace<StayOnMap_Tag>(truck);
    m_registry->emplace<Transform>(truck, vec2f(300.0, 350.0), vec2f(1.0, 1.0), 0.0);
    m_registry->emplace<Velocity>(truck, 20.0, vec2f(-1.0, 0.0));
    m_registry->emplace<Sprite>(truck, "truck-image", 32, 32, 2);
    m_registry->emplace<ProjectileEmitter>(truck, 100.0, vec2f(1.0, -1.0), 2000, 10000, 10);
    m_registry->emplace<Health>(truck, 100);
    m_registry->emplace<BoxCollider>(truck, 32, 32);

    const auto treeA = m_registry->create();
    m_registry->emplace<Obstacle_Tag>(treeA);
    m_registry->emplace<Transform>(treeA, vec2f(200.0, 345.0), vec2f(1.0, 1.0), 0.0);
    m_registry->emplace<Sprite>(treeA, "tree-image", 16, 32, 1);
    m_registry->emplace<BoxCollider>(treeA, 16, 32);

    const auto treeB = m_registry->create();
    m_registry->emplace<Obstacle_Tag>(treeB);
    m_registry->emplace<Transform>(treeB, vec2f(400.0, 345.0), vec2f(1.0, 1.0), 0.0);
    m_registry->emplace<Sprite>(treeB, "tree-image", 16, 32, 1);
    m_registry->emplace<BoxCollider>(treeB, 16, 32);

    const auto label = m_registry->create();
    m_registry->emplace<UI_Tag>(label);
    SDL_Color green = {30, 200, 30};
    m_registry->emplace<TextLabel>(label, vec2f(WINDOWWIDTH / 2 - 40, 10), "- Hub Scene- ", "charriot-font", green, true);

    const auto trigger = m_registry->create();
    m_registry->emplace<Transform>(trigger, vec2f(0.0, 0.0), vec2f(1.0, 1.0), 0.0);
    m_registry->emplace<BoxCollider>(trigger, 30, 30);
    m_registry->emplace<SceneSwitcher>(trigger, "Game", "Garden");
}

void Hub::UnloadScene()
{
}
