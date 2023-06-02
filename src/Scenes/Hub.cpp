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

    std::pair<std::string, std::string> mapInfo = XMLHandler::GetMapInfoFromXML("assets/levels/TheHub.xml");
    LoadMap(mapInfo.first, mapInfo.second);
    XMLHandler::LoadFromXML(m_registry, m_renderer, m_assetStore, "assets/levels/TheHub.xml");
    // XMLHandler::SaveToXML(m_registry);
}

void Hub::UnloadScene()
{
}
