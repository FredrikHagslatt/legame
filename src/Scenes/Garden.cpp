#include "Garden.h"

void Garden::UpdateScene(const double elapsedTime)
{
}
void Garden::RenderScene(const double elapsedTime)
{
}

void Garden::LoadScene()
{
    LoadMap("assets/tilemaps/themes/ground_tiles.png", "assets/tilemaps/maps/garden.map");

    m_assetStore->AddTexture(m_renderer, "cabin-image", "assets/images/buildings/log_cabin.png");
    m_assetStore->AddTexture(m_renderer, "radar-image", "assets/images/radar.png");

    m_assetStore->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
    m_assetStore->AddFont("pico8-font-5", "assets/fonts/pico8.ttf", 5);
    m_assetStore->AddFont("pico8-font-10", "assets/fonts/pico8.ttf", 10);

    const auto cabin = m_registry->create();
    m_registry->emplace<Obstacle_Tag>(cabin);
    m_registry->emplace<Transform>(cabin, vec2f(400, 150.0));
    m_registry->emplace<Sprite>(cabin, "cabin-image", 122, 96, 96);
    m_registry->emplace<BoxCollider>(cabin, 122, 80, vec2f(0, 16));

    const auto cabinEntry = m_registry->create();
    m_registry->emplace<Trigger_Tag>(cabinEntry);
    m_registry->emplace<Transform>(cabinEntry, vec2f(480, 430.0));
    m_registry->emplace<BoxCollider>(cabinEntry, 16, 4);
    m_registry->emplace<SceneSwitcher>(cabinEntry, "Game", "Hub");

    const auto radar = m_registry->create();
    m_registry->emplace<UI_Tag>(radar);
    m_registry->emplace<Transform>(radar, vec2f(WINDOWWIDTH - 74, 10.0), 0.25);
    m_registry->emplace<Sprite>(radar, "radar-image", 64, 64, 0, true);
    m_registry->emplace<Animation>(radar, 8, 5, true);

    const auto label = m_registry->create();
    m_registry->emplace<UI_Tag>(label);
    SDL_Color green = {30, 200, 30};
    m_registry->emplace<TextLabel>(label, vec2f(WINDOWWIDTH / 2 - 40, 10), "- Garden Scene -", "charriot-font", green, true);
}

void Garden::UnloadScene()
{
}
