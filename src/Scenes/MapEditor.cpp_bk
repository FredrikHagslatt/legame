#include <fstream>
#include <filesystem>
#include "MapEditor.h"
#include "Constants.h"
#include "Events/EventDispatcher.h"
#include "DevTools/DevTools.h"

void MapEditor::UpdateMapSize()
{
    if (m_queuedMapNumCols > m_mapNumCols)
    {
        IncreaseMapWidth(m_queuedMapNumCols);
    }
    else if (m_queuedMapNumCols < m_mapNumCols)
    {
        DecreaseMapWidth(m_queuedMapNumCols);
    }

    if (m_queuedMapNumRows > m_mapNumRows)
    {
        IncreaseMapHeight(m_queuedMapNumRows);
    }
    else if (m_queuedMapNumRows < m_mapNumRows)
    {
        DecreaseMapHeight(m_queuedMapNumRows);
    }

    m_mapWidth = m_mapNumCols * TILESIZE * SCALE;
    m_mapHeight = m_mapNumRows * TILESIZE * SCALE;
}

void MapEditor::IncreaseMapWidth(int newNumCols)
{
    for (int y = 0; y < m_mapNumRows; y++)
    {
        for (int x = m_mapNumCols; x < newNumCols; x++)
        {
            const auto tile = m_registry->create();
            m_registry->emplace<Tile_Tag>(tile);
            m_registry->emplace<Transform>(tile, vec2f(x * SCALE * TILESIZE, y * SCALE * TILESIZE));
            m_registry->emplace<Sprite>(tile, m_theme, TILESIZE, TILESIZE, false, 0, 0);
        }
    }
    m_mapNumCols = newNumCols;
}

void MapEditor::DecreaseMapWidth(int newNumCols)
{
    auto view = m_registry->view<Tile_Tag, Transform>();
    for (auto tile : view)
    {
        auto transform = view.get<Transform>(tile);

        if (transform.position.x >= newNumCols * TILESIZE * SCALE)
        {
            Game::entitiesToKill.push_back(tile);
        }
    }
    m_mapNumCols = newNumCols;
}

void MapEditor::IncreaseMapHeight(int newNumRows)
{
    for (int x = 0; x < m_mapNumCols; x++)
    {
        for (int y = m_mapNumRows; y < newNumRows; y++)
        {
            const auto tile = m_registry->create();
            m_registry->emplace<Tile_Tag>(tile);
            m_registry->emplace<Transform>(tile, vec2f(x * SCALE * TILESIZE, y * SCALE * TILESIZE));
            m_registry->emplace<Sprite>(tile, m_theme, TILESIZE, TILESIZE, false, 0, 0);
        }
    }
    m_mapNumRows = newNumRows;
}

void MapEditor::DecreaseMapHeight(int newNumRows)
{
    auto view = m_registry->view<Tile_Tag, Transform>();
    for (auto tile : view)
    {
        auto transform = view.get<Transform>(tile);

        if (transform.position.y >= newNumRows * TILESIZE * SCALE)
        {
            Game::entitiesToKill.push_back(tile);
        }
    }
    m_mapNumRows = newNumRows;
}

void MapEditor::SelectTile(const MouseMotionEvent &event)
{
    int mouseX = event.motion.x;
    int mouseY = event.motion.y;

    auto view = m_registry->view<Tile_Tag, Transform>();

    for (auto &entity : view)
    {
        const auto transform = view.get<Transform>(entity);
        auto &m_tileBrushTransform = m_registry->get<Transform>(m_tileBrush);

        if (mouseX >= transform.position.x - camera.x && mouseX <= transform.position.x - camera.x + TILESIZE * SCALE && mouseY >= transform.position.y - camera.y && mouseY <= transform.position.y - camera.y + TILESIZE * SCALE)
        {
            m_selectedTile = std::make_unique<entt::entity>(entity);
            m_tileBrushTransform.position = transform.position;
            return;
        }
        m_selectedTile = nullptr;
        m_tileBrushTransform.position = vec2f(1000000, 1000000); // Far outside the visible area
    }
}

void MapEditor::PlaceTile()
{
    if (m_selectedTile)
    {
        auto &sprite = m_registry->get<Sprite>(*m_selectedTile);
        const auto brushSprite = m_registry->get<Sprite>(m_tileBrush);
        sprite.srcRect = brushSprite.srcRect;
    }
}

void MapEditor::SaveMap(const std::string filename)
{
    Logger::Info("Saving map: " + filename + "  |  Map should be found in project root or build dir");

    std::ofstream mapFile;
    mapFile.open(filename);

    std::vector<std::vector<entt::entity>> tiles(
        m_mapNumRows,
        std::vector<entt::entity>(m_mapNumCols));

    // Arranging tiles in grid to be saved
    auto view = m_registry->view<Tile_Tag, Transform, Sprite>();
    for (auto entity : view)
    {
        const auto transform = view.get<Transform>(entity);
        tiles[transform.position.y / (TILESIZE * SCALE)][transform.position.x / (TILESIZE * SCALE)] = entity;
    }

    // Save map
    for (const auto row : tiles)
    {
        for (const auto entity : row)
        {
            const auto sprite = view.get<Sprite>(entity);
            std::string subSpriteCoordinate = std::to_string(sprite.srcRect.y / TILESIZE) + std::to_string(sprite.srcRect.x / TILESIZE);
            mapFile << subSpriteCoordinate << ',';
        }
        mapFile << '\n';
    }
    mapFile.close();
}

std::vector<std::string> MapEditor::GetThemes()
{
    std::string path = "assets/tilemaps/themes/";
    std::vector<std::string> themes;
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        themes.push_back(entry.path().string());
    }
    return themes;
}

void MapEditor::SelectTheme(std::string themeAssetId)
{
    Logger::Info("Selecting theme: " + themeAssetId);
    m_theme = themeAssetId;
    const auto view = m_registry->view<Tile_Tag, Sprite>();

    // Tilemap theme
    for (auto entity : view)
    {
        auto &sprite = view.get<Sprite>(entity);
        sprite.assetId = themeAssetId;
    }

    // Brush theme
    auto &sprite = m_registry->get<Sprite>(m_tileBrush);
    sprite.assetId = themeAssetId;
}

void MapEditor::OnMouseMotionEvent(const MouseMotionEvent &event)
{
    SelectTile(event);
}
void MapEditor::OnMouseButtonPressedEvent(const MouseButtonPressedEvent &event)
{
    m_leftMouseHeld = true;
    // Contitional entity creation here
}

void MapEditor::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent &event)
{
    m_leftMouseHeld = false;
}

void MapEditor::UpdateScene(const double elapsedTime)
{
    m_queuedMapNumCols = std::max(1, m_queuedMapNumCols);
    m_queuedMapNumRows = std::max(1, m_queuedMapNumRows);
    UpdateMapSize();

    if (m_leftMouseHeld)
    {
        PlaceTile();
    }
}

void MapEditor::RenderScene(const double elapsedTime)
{

    if (DevTools::showDevTools)
    { // To prevent the different ImGui windows from fighting over inputs
        return;
    }

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

    if (ImGui::Begin("Map Editor", NULL, window_flags))
    {

        if (ImGui::CollapsingHeader("Map size"))
        {
            ImGui::InputInt("Width in tiles", &m_queuedMapNumCols);
            ImGui::InputInt("Height in tiles", &m_queuedMapNumRows);
        }

        if (ImGui::CollapsingHeader("Theme selector"))
        {
            std::vector<std::string> themes = GetThemes();
            static int selected = -1;
            for (int n = 0; n < themes.size(); n++)
            {
                char buf[64];
                sprintf(buf, themes.at(n).c_str());
                if (ImGui::Selectable(buf, selected == n))
                {
                    SelectTheme(themes.at(n));
                    selected = n;
                }
            }
        }

        if (ImGui::CollapsingHeader("Tile selector"))
        {
            SDL_Texture *texture = m_assetStore->GetTexture(m_theme);
            int textureWidth, textureHeight;
            SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

            for (int y = 0; y < textureHeight / TILESIZE; y++)
            {
                for (int x = 0; x < textureWidth / TILESIZE; x++)
                {
                    ImGui::PushID(10 * y + x);
                    int padding = 0;
                    ImVec2 size = ImVec2(TILESIZE * SCALE, TILESIZE * SCALE);
                    ImVec2 subSpriteTopLeftCorner = ImVec2(float(TILESIZE) * x / textureWidth, float(TILESIZE) * y / textureHeight);
                    ImVec2 subSpriteBotRightCorner = ImVec2(float(TILESIZE) * (x + 1) / textureWidth, float(TILESIZE) * (y + 1) / textureHeight);
                    ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);   // Black background
                    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
                    if (ImGui::ImageButton(texture, size, subSpriteTopLeftCorner, subSpriteBotRightCorner, padding, bg_col, tint_col))
                    {
                        Logger::Info("Selecting sub sprite { x: " + std::to_string(x) + ", y: " + std::to_string(y) + " }");

                        auto &sprite = m_registry->get<Sprite>(m_tileBrush);
                        sprite.srcRect =
                            {
                                x * TILESIZE,
                                y * TILESIZE,
                                TILESIZE,
                                TILESIZE};
                    }
                    ImGui::PopID();
                    ImGui::SameLine();
                }
                ImGui::NewLine();
            }
        }

        static char filename[64] = "generated.map";
        ImGui::InputText("##emptyID", filename, IM_ARRAYSIZE(filename));
        ImGui::SameLine();
        if (ImGui::Button("Save map##Button"))
        {
            SaveMap(std::string(filename));
        }
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void MapEditor::LoadScene()
{
    DevTools::showDevTools = false;

    std::vector<std::string> themes = GetThemes();
    for (std::string theme : themes)
    {
        m_assetStore->AddTexture(m_renderer, theme, theme);
    }

    LoadMap(m_theme, "assets/tilemaps/maps/map_editor.map");

    m_tileBrush = m_registry->create();
    m_registry->emplace<Transform>(m_tileBrush, vec2f(0));
    m_registry->emplace<Sprite>(m_tileBrush, m_theme, TILESIZE, TILESIZE, false, 0, 0);

    m_queuedMapNumCols = m_mapWidth / TILESIZE / SCALE;
    m_queuedMapNumRows = m_mapHeight / TILESIZE / SCALE;
    m_mapNumCols = m_queuedMapNumCols;
    m_mapNumRows = m_queuedMapNumRows;

    m_assetStore->AddTexture(m_renderer, "bullet-image", "assets/images/bullet.png");
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

    Event::dispatcher.sink<MouseMotionEvent>().connect<&MapEditor::OnMouseMotionEvent>(this);
    Event::dispatcher.sink<MouseButtonPressedEvent>().connect<&MapEditor::OnMouseButtonPressedEvent>(this);
    Event::dispatcher.sink<MouseButtonReleasedEvent>().connect<&MapEditor::OnMouseButtonReleasedEvent>(this);
}

void MapEditor::UnloadScene()
{
    Event::dispatcher.sink<MouseMotionEvent>().disconnect<&MapEditor::OnMouseMotionEvent>(this);
    Event::dispatcher.sink<MouseButtonPressedEvent>().disconnect<&MapEditor::OnMouseButtonPressedEvent>(this);
    Event::dispatcher.sink<MouseButtonReleasedEvent>().disconnect<&MapEditor::OnMouseButtonReleasedEvent>(this);
}
