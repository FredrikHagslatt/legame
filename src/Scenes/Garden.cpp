#include "Garden.h"

void Garden::UpdateScene(double elapsedTime)
{
}
void Garden::RenderScene(double elapsedTime)
{
}

void Garden::LoadScene()
{

    LoadMap("assets/tilemaps/ground_tiles.png", "assets/tilemaps/jungle.map");

    m_assetStore->AddTexture(m_renderer, "spike-image", "assets/images/Spike.png");
    m_assetStore->AddTexture(m_renderer, "radar-image", "assets/images/radar.png");

    m_assetStore->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
    m_assetStore->AddFont("pico8-font-5", "assets/fonts/pico8.ttf", 5);
    m_assetStore->AddFont("pico8-font-10", "assets/fonts/pico8.ttf", 10);

    const auto player = m_registry->create();
    m_registry->emplace<Player_Tag>(player);
    m_registry->emplace<StayOnMap_Tag>(player);
    m_registry->emplace<Transform>(player, glm::vec2(200.0, 400.0), glm::vec2(3.0, 3.0), 0.0);
    m_registry->emplace<Velocity>(player, 0.0, 0.0);
    m_registry->emplace<Sprite>(player, "spike-image", 16, 32, 10);
    m_registry->emplace<Animation>(player, 5, 5, true);
    m_registry->emplace<KeyboardControlled>(player, glm::vec2(0, -200), glm::vec2(200, 0), glm::vec2(0, 200), glm::vec2(-200, 0));
    m_registry->emplace<ProjectileEmitter>(player, glm::vec2(300.0, 300.0), 0, 10000, 10, true);
    m_registry->emplace<Health>(player, 100);
    m_registry->emplace<BoxCollider>(player, 16, 32);

    const auto radar = m_registry->create();
    m_registry->emplace<UI_Tag>(radar);
    m_registry->emplace<Transform>(radar, glm::vec2(WINDOWWIDTH - 74, 10.0), glm::vec2(1.0, 1.0), 0.0);
    m_registry->emplace<Sprite>(radar, "radar-image", 64, 64, 100, true);
    m_registry->emplace<Animation>(radar, 8, 5, true);

    const auto label = m_registry->create();
    m_registry->emplace<UI_Tag>(label);
    SDL_Color green = {30, 200, 30};
    m_registry->emplace<TextLabel>(label, glm::vec2(WINDOWWIDTH / 2 - 40, 10), "- Garden Scene -", "charriot-font", green, true);
}

void Garden::UnloadScene()
{
}
