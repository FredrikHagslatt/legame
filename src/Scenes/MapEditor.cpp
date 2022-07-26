#include "MapEditor.h"
#include "Constants.h"

void MapEditor::UpdateScene(const double elapsedTime)
{
}
void MapEditor::RenderScene(const double elapsedTime)
{
}

void MapEditor::LoadScene()
{
    LoadMap("assets/tilemaps/ground_tiles.png", "assets/tilemaps/map_editor.map");

    m_assetStore->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);
    m_assetStore->AddFont("pico8-font-5", "assets/fonts/pico8.ttf", 5);

    const auto label = m_registry->create();
    m_registry->emplace<UI_Tag>(label);
    SDL_Color green = {30, 200, 30};
    m_registry->emplace<TextLabel>(label, vec2f(WINDOWWIDTH / 2 - 40, 10), "- Map Editor - ", "charriot-font", green, true);

    auto view = m_registry->view<Transform, Player_Tag>();
    for (auto player : view)
    {
        auto &transform = view.get<Transform>(player);
        transform.position = vec2f(0.0, 0.0);
    }
}

void MapEditor::UnloadScene()
{
}
