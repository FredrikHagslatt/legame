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

    assetStore.AddTexture(renderer, "spike-image", "assets/images/Spike.png");
    assetStore.AddTexture(renderer, "tank-image", "assets/images/tank-panther-right.png");
    assetStore.AddTexture(renderer, "truck-image", "assets/images/truck-ford-right.png");
    assetStore.AddTexture(renderer, "tree-image", "assets/images/tree.png");
    assetStore.AddTexture(renderer, "chopper-image", "assets/images/chopper-spritesheet.png");
    assetStore.AddTexture(renderer, "radar-image", "assets/images/radar.png");
    assetStore.AddTexture(renderer, "bullet-image", "assets/images/bullet.png");

    assetStore.AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
    assetStore.AddFont("pico8-font-5", "assets/fonts/pico8.ttf", 5);
    assetStore.AddFont("pico8-font-10", "assets/fonts/pico8.ttf", 10);

    const auto player = registry.create();
    registry.emplace<Player_Tag>(player);
    registry.emplace<StayOnMap_Tag>(player);
    registry.emplace<Transform>(player, glm::vec2(200.0, 400.0), glm::vec2(4.0, 4.0), 0.0);
    registry.emplace<Velocity>(player, 0.0, 0.0);
    registry.emplace<Sprite>(player, "spike-image", 16, 32, 10);
    registry.emplace<Animation>(player, 5, 5, true);
    registry.emplace<KeyboardControlled>(player, glm::vec2(0, -200), glm::vec2(200, 0), glm::vec2(0, 200), glm::vec2(-200, 0));
    registry.emplace<ProjectileEmitter>(player, glm::vec2(300.0, 300.0), 0, 10000, 10, true);
    registry.emplace<Health>(player, 100);
    registry.emplace<BoxCollider>(player, 16, 32);

    const auto chopper = registry.create();
    registry.emplace<StayOnMap_Tag>(chopper);
    registry.emplace<Transform>(chopper, glm::vec2(100.0, 100.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Velocity>(chopper, 50.0, 0.0);
    registry.emplace<Sprite>(chopper, "chopper-image", 32, 32, 10);
    registry.emplace<Animation>(chopper, 2, 12, true);
    registry.emplace<ProjectileEmitter>(chopper, glm::vec2(300.0, 300.0), 0, 10000, 10, true);
    registry.emplace<Health>(chopper, 100);
    registry.emplace<BoxCollider>(chopper, 32, 32);

    const auto radar = registry.create();
    registry.emplace<UI_Tag>(radar);
    registry.emplace<Transform>(radar, glm::vec2(WINDOWWIDTH - 74, 10.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Sprite>(radar, "radar-image", 64, 64, 100, true);
    registry.emplace<Animation>(radar, 8, 5, true);

    const auto tank = registry.create();
    registry.emplace<Enemy_Tag>(tank);
    registry.emplace<StayOnMap_Tag>(tank);
    registry.emplace<Transform>(tank, glm::vec2(120.0, 300.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Velocity>(tank, 30.0, 0.0);
    registry.emplace<Sprite>(tank, "tank-image", 32, 32, 2);
    registry.emplace<ProjectileEmitter>(tank, glm::vec2(100.0, 0.0), 1000, 10000, 10, false);
    registry.emplace<Health>(tank, 100);
    registry.emplace<BoxCollider>(tank, 32, 32);

    const auto truck = registry.create();
    registry.emplace<Enemy_Tag>(truck);
    registry.emplace<StayOnMap_Tag>(truck);
    registry.emplace<Transform>(truck, glm::vec2(300.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Velocity>(truck, 20.0, 0.0);
    registry.emplace<Sprite>(truck, "truck-image", 32, 32, 2);
    registry.emplace<ProjectileEmitter>(truck, glm::vec2(100.0, -100.0), 2000, 10000, 10, false);
    registry.emplace<Health>(truck, 100);
    registry.emplace<BoxCollider>(truck, 32, 32);

    const auto treeA = registry.create();
    registry.emplace<Obstacle_Tag>(treeA);
    registry.emplace<Transform>(treeA, glm::vec2(200.0, 345.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Sprite>(treeA, "tree-image", 16, 32, 1);
    registry.emplace<BoxCollider>(treeA, 16, 32);

    const auto treeB = registry.create();
    registry.emplace<Obstacle_Tag>(treeB);
    registry.emplace<Transform>(treeB, glm::vec2(400.0, 345.0), glm::vec2(1.0, 1.0), 0.0);
    registry.emplace<Sprite>(treeB, "tree-image", 16, 32, 1);
    registry.emplace<BoxCollider>(treeB, 16, 32);

    const auto label = registry.create();
    registry.emplace<UI_Tag>(label);
    SDL_Color green = {30, 200, 30};
    registry.emplace<TextLabel>(label, glm::vec2(WINDOWWIDTH / 2 - 40, 10), "Example Title 1.0", "charriot-font", green, true);
}

void Hub::UnloadScene()
{
}
