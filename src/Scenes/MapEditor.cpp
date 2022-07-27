#include "MapEditor.h"
#include "Constants.h"

void MapEditor::UpdateMapSize()
{
    if (queuedMapWidth > Game::mapWidth)
    {
        IncreaseMapWidth(Game::mapWidth, queuedMapWidth);
    }
    else if (queuedMapWidth < Game::mapWidth)
    {
        DecreaseMapWidth(queuedMapWidth);
    }

    if (queuedMapHeight > Game::mapHeight)
    {
        IncreaseMapHeight(Game::mapHeight, queuedMapHeight);
    }
    else if (queuedMapHeight < Game::mapHeight)
    {
        DecreaseMapHeight(queuedMapHeight);
    }
}

void MapEditor::IncreaseMapWidth(int oldWidth, int newWidth)
{
}

void MapEditor::DecreaseMapWidth(int newWidth)
{
    auto view = m_registry->view<Tile_Tag, Transform>();
    for (auto tile : view)
    {
        auto transform = view.get<Transform>(tile);

        if (transform.position.x >= newWidth * TILESIZE * SCALE)
        {
            Game::entitiesToKill.push_back(tile);
        }
    }
    Game::mapWidth = newWidth;
}

void MapEditor::IncreaseMapHeight(int oldHeight, int newHeight)
{
}

void MapEditor::DecreaseMapHeight(int newHeight)
{

    auto view = m_registry->view<Tile_Tag, Transform>();
    for (auto tile : view)
    {
        auto transform = view.get<Transform>(tile);

        if (transform.position.y >= newHeight * TILESIZE * SCALE)
        {
            Game::entitiesToKill.push_back(tile);
        }
    }

    Game::mapHeight = newHeight;
}

void MapEditor::UpdateScene(const double elapsedTime)
{
    queuedMapWidth = std::max(1, queuedMapWidth);
    queuedMapHeight = std::max(1, queuedMapHeight);

    UpdateMapSize();
}
void MapEditor::RenderScene(const double elapsedTime)
{

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
    if (ImGui::Begin("Map Editor", NULL, window_flags))
    {

        ImGui::InputInt("Map Width", &queuedMapWidth);
        ImGui::InputInt("Map Height", &queuedMapHeight);
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
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
