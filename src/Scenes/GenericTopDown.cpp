#include "GenericTopDown.h"
#include "Constants.h"
#include "XMLHandler/XMLHandler.h"

void GenericTopDown::UpdateScene(const double elapsedTime)
{
}
void GenericTopDown::RenderScene(const double elapsedTime)
{
}

void GenericTopDown::LoadScene(std::string level)
{
    std::pair<std::string, std::string> mapInfo = XMLHandler::GetMapInfoFromXML(level);
    LoadMap(mapInfo.first, mapInfo.second);
    XMLHandler::LoadFromXML(m_registry, m_renderer, m_assetStore, level);
}

void GenericTopDown::UnloadScene()
{
}
