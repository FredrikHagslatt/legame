#include "Garden.h"

void Garden::UpdateScene(const double elapsedTime)
{
}
void Garden::RenderScene(const double elapsedTime)
{
}

void Garden::LoadScene()
{
    std::pair<std::string, std::string> mapInfo = XMLHandler::GetMapInfoFromXML("assets/levels/Garden.xml");
    LoadMap(mapInfo.first, mapInfo.second);
    XMLHandler::LoadFromXML(m_registry, m_renderer, m_assetStore, "assets/levels/Garden.xml");
}

void Garden::UnloadScene()
{
}
