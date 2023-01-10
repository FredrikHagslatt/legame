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

    XMLHandler::LoadFromXML(m_registry, "assets/levels/Garden.xml");
}

void Garden::UnloadScene()
{
}
