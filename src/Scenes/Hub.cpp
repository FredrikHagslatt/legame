#include "Hub.h"
#include "Constants.h"
#include "XMLHandler/XMLHandler.h"

void Hub::UpdateScene(const double elapsedTime)
{
}
void Hub::RenderScene(const double elapsedTime)
{
}

void Hub::LoadScene()
{

    LoadMap("assets/tilemaps/themes/ground_tiles.png", "assets/tilemaps/maps/hub.map");

    m_assetStore->AddTexture(m_renderer, "tank-image", "assets/images/tank-panther-right.png");
    m_assetStore->AddTexture(m_renderer, "truck-image", "assets/images/truck-ford-right.png");
    m_assetStore->AddTexture(m_renderer, "tree-image", "assets/images/tree.png");
    m_assetStore->AddTexture(m_renderer, "chopper-image", "assets/images/chopper-spritesheet.png");
    m_assetStore->AddTexture(m_renderer, "radar-image", "assets/images/radar.png");
    m_assetStore->AddTexture(m_renderer, "bullet-image", "assets/images/bullet.png");

    m_assetStore->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
    m_assetStore->AddFont("pico8-font-5", "assets/fonts/pico8.ttf", 5);
    m_assetStore->AddFont("pico8-font-10", "assets/fonts/pico8.ttf", 10);

    XMLHandler::LoadFromXML(m_registry, "assets/levels/TheHub.xml");
    // XMLHandler::SaveToXML(m_registry);
}

void Hub::UnloadScene()
{
}
