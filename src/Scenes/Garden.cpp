#include "Garden.h"

void Garden::UpdateScene(double elapsedTime)
{
}
void Garden::RenderScene(double elapsedTime)
{
}

void Garden::LoadScene()
{
    LoadMap("assets/tilemaps/ground_tiles.png", "assets/tilemaps/yard.map");

    m_assetStore->AddTexture(m_renderer, "radar-image", "assets/images/radar.png");

    m_assetStore->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
    m_assetStore->AddFont("pico8-font-5", "assets/fonts/pico8.ttf", 5);
    m_assetStore->AddFont("pico8-font-10", "assets/fonts/pico8.ttf", 10);

    const auto radar = m_registry->create();
    m_registry->emplace<UI_Tag>(radar);
    m_registry->emplace<Transform>(radar, vec2f(WINDOWWIDTH - 74, 10.0), vec2f(1.0, 1.0), 0.0);
    m_registry->emplace<Sprite>(radar, "radar-image", 64, 64, 100, true);
    m_registry->emplace<Animation>(radar, 8, 5, true);

    const auto label = m_registry->create();
    m_registry->emplace<UI_Tag>(label);
    SDL_Color green = {30, 200, 30};
    m_registry->emplace<TextLabel>(label, vec2f(WINDOWWIDTH / 2 - 40, 10), "- Garden Scene -", "charriot-font", green, true);
}

void Garden::UnloadScene()
{
}
