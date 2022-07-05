#include "Hub.h"

void Hub::UpdateScene(double elapsedTime)
{
}
void Hub::RenderScene(double elapsedTime)
{
}

void Hub::LoadScene()
{

    LoadMap("assets/tilemaps/ground_tiles.png", "assets/tilemaps/hub.map");

    m_assetStore->AddTexture(m_renderer, "spike-image", "assets/images/Spike.png");
    m_assetStore->AddTexture(m_renderer, "tank-image", "assets/images/tank-panther-right.png");
    m_assetStore->AddTexture(m_renderer, "truck-image", "assets/images/truck-ford-right.png");
    m_assetStore->AddTexture(m_renderer, "tree-image", "assets/images/tree.png");
    m_assetStore->AddTexture(m_renderer, "chopper-image", "assets/images/chopper-spritesheet.png");
    m_assetStore->AddTexture(m_renderer, "radar-image", "assets/images/radar.png");
    m_assetStore->AddTexture(m_renderer, "bullet-image", "assets/images/bullet.png");

    m_assetStore->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
    m_assetStore->AddFont("pico8-font-5", "assets/fonts/pico8.ttf", 5);
    m_assetStore->AddFont("pico8-font-10", "assets/fonts/pico8.ttf", 10);

    const auto player = m_registry->create();
    m_registry->emplace<Player_Tag>(player);
    m_registry->emplace<StayOnMap_Tag>(player);
    m_registry->emplace<Transform>(player, glm::vec2(200.0, 400.0), glm::vec2(4.0, 4.0), 0.0);
    m_registry->emplace<Velocity>(player, 0.0, 0.0);
    m_registry->emplace<Sprite>(player, "spike-image", 16, 32, 10);
    m_registry->emplace<Animation>(player, 5, 5, true);
    m_registry->emplace<KeyboardControlled>(player, glm::vec2(0, -200), glm::vec2(200, 0), glm::vec2(0, 200), glm::vec2(-200, 0));
    m_registry->emplace<ProjectileEmitter>(player, glm::vec2(300.0, 300.0), 0, 10000, 10, true);
    m_registry->emplace<Health>(player, 100);
    m_registry->emplace<BoxCollider>(player, 16, 32);

    const auto chopper = m_registry->create();
    m_registry->emplace<StayOnMap_Tag>(chopper);
    m_registry->emplace<Transform>(chopper, glm::vec2(100.0, 100.0), glm::vec2(1.0, 1.0), 0.0);
    m_registry->emplace<Velocity>(chopper, 50.0, 0.0);
    m_registry->emplace<Sprite>(chopper, "chopper-image", 32, 32, 10);
    m_registry->emplace<Animation>(chopper, 2, 12, true);
    m_registry->emplace<ProjectileEmitter>(chopper, glm::vec2(300.0, 300.0), 0, 10000, 10, true);
    m_registry->emplace<Health>(chopper, 100);
    m_registry->emplace<BoxCollider>(chopper, 32, 32);

    const auto radar = m_registry->create();
    m_registry->emplace<UI_Tag>(radar);
    m_registry->emplace<Transform>(radar, glm::vec2(WINDOWWIDTH - 74, 10.0), glm::vec2(1.0, 1.0), 0.0);
    m_registry->emplace<Sprite>(radar, "radar-image", 64, 64, 100, true);
    m_registry->emplace<Animation>(radar, 8, 5, true);

    const auto tank = m_registry->create();
    m_registry->emplace<Enemy_Tag>(tank);
    m_registry->emplace<StayOnMap_Tag>(tank);
    m_registry->emplace<Transform>(tank, glm::vec2(120.0, 300.0), glm::vec2(1.0, 1.0), 0.0);
    m_registry->emplace<Velocity>(tank, 30.0, 0.0);
    m_registry->emplace<Sprite>(tank, "tank-image", 32, 32, 2);
    m_registry->emplace<ProjectileEmitter>(tank, glm::vec2(100.0, 0.0), 1000, 10000, 10, false);
    m_registry->emplace<Health>(tank, 100);
    m_registry->emplace<BoxCollider>(tank, 32, 32);

    const auto truck = m_registry->create();
    m_registry->emplace<Enemy_Tag>(truck);
    m_registry->emplace<StayOnMap_Tag>(truck);
    m_registry->emplace<Transform>(truck, glm::vec2(300.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
    m_registry->emplace<Velocity>(truck, 20.0, 0.0);
    m_registry->emplace<Sprite>(truck, "truck-image", 32, 32, 2);
    m_registry->emplace<ProjectileEmitter>(truck, glm::vec2(100.0, -100.0), 2000, 10000, 10, false);
    m_registry->emplace<Health>(truck, 100);
    m_registry->emplace<BoxCollider>(truck, 32, 32);

    const auto treeA = m_registry->create();
    m_registry->emplace<Obstacle_Tag>(treeA);
    m_registry->emplace<Transform>(treeA, glm::vec2(200.0, 345.0), glm::vec2(1.0, 1.0), 0.0);
    m_registry->emplace<Sprite>(treeA, "tree-image", 16, 32, 1);
    m_registry->emplace<BoxCollider>(treeA, 16, 32);

    const auto treeB = m_registry->create();
    m_registry->emplace<Obstacle_Tag>(treeB);
    m_registry->emplace<Transform>(treeB, glm::vec2(400.0, 345.0), glm::vec2(1.0, 1.0), 0.0);
    m_registry->emplace<Sprite>(treeB, "tree-image", 16, 32, 1);
    m_registry->emplace<BoxCollider>(treeB, 16, 32);

    const auto label = m_registry->create();
    m_registry->emplace<UI_Tag>(label);
    SDL_Color green = {30, 200, 30};
    m_registry->emplace<TextLabel>(label, glm::vec2(WINDOWWIDTH / 2 - 40, 10), "Example Title 1.0", "charriot-font", green, true);
}

void Hub::UnloadScene()
{
}
