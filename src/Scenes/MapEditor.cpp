#include <fstream>
#include <filesystem>
#include <algorithm>
#include "MapEditor.h"
#include "Constants.h"
#include "Events/EventDispatcher.h"
#include "DevTools/DevTools.h"

void MapEditor::UpdateMapSize()
{
    if (m_queuedMapNumCols > m_mapNumCols)
    {
        IncreaseMapWidth();
    }
    else if (m_queuedMapNumCols < m_mapNumCols)
    {
        DecreaseMapWidth();
    }

    if (m_queuedMapNumRows > m_mapNumRows)
    {
        IncreaseMapHeight();
    }
    else if (m_queuedMapNumRows < m_mapNumRows)
    {
        DecreaseMapHeight();
    }

    m_mapWidth = m_mapNumCols * TILESIZE * SCALE;
    m_mapHeight = m_mapNumRows * TILESIZE * SCALE;
}

void MapEditor::IncreaseMapWidth()
{
    while (m_queuedMapNumCols > m_mapNumCols)
    {
        for (int y = 0; y < m_tileMap.size(); y++)
        {
            Sprite neighborSprite = m_tileMap.at(y).back();
            m_tileMap.at(y).push_back(neighborSprite);
        }
        m_mapNumCols++;
    }
}

void MapEditor::DecreaseMapWidth()
{
    while (m_queuedMapNumCols < m_mapNumCols)
    {
        for (int y = 0; y < m_tileMap.size(); y++)
        {
            m_tileMap.at(y).pop_back();
        }
        m_mapNumCols--;
    }
}

void MapEditor::IncreaseMapHeight()
{
    while (m_queuedMapNumRows > m_mapNumRows)
    {
        m_tileMap.push_back(std::vector<Sprite>{});
        for (int x = 0; x < m_tileMap.at(0).size(); x++)
        {
            Sprite neighborSprite = m_tileMap.at(m_mapNumRows - 1).at(x);
            m_tileMap.back().push_back(neighborSprite);
        }
        m_mapNumRows++;
    }
}

void MapEditor::DecreaseMapHeight()
{
    while (m_queuedMapNumRows < m_mapNumRows)
    {
        m_tileMap.pop_back();
        m_mapNumRows--;
    }
}

void MapEditor::SelectTile(const MouseMotionEvent &event)
{
    auto &m_tileBrushTransform = m_registry->get<Transform>(m_tileBrush);
    vec2i mousePos = vec2i(event.motion.x + m_camera.x, event.motion.y + m_camera.y);

    if (
        mousePos.x >= 0 &&
        mousePos.x < m_mapWidth &&
        mousePos.y >= 0 &&
        mousePos.y < m_mapHeight)
    {
        m_tileIsSelected = true;
        m_selectedTile = vec2i(static_cast<int>((mousePos.x) / (TILESIZE * SCALE)), static_cast<int>((mousePos.y) / (TILESIZE * SCALE)));
        m_tileBrushTransform.position = vec2f(m_selectedTile.x * TILESIZE * SCALE, m_selectedTile.y * TILESIZE * SCALE);
    }
    else
    {
        m_tileIsSelected = false;
        m_tileBrushTransform.position = vec2f(-1000 * TILESIZE * SCALE, -1000 * TILESIZE * SCALE); // Far outside the map
    }
}

void MapEditor::PlaceTile()
{
    if (m_tileIsSelected)
    {
        Sprite &sprite = m_tileMap.at(m_selectedTile.y).at(m_selectedTile.x);
        const auto brushSprite = m_registry->get<Sprite>(m_tileBrush);
        sprite.srcRect = brushSprite.srcRect;
    }
}

void MapEditor::SaveMap(const std::string filename)
{
    Logger::Info("Saving map: " + filename + "  |  Map should be found in project root or build dir");

    std::ofstream mapFile;
    mapFile.open(filename);

    // Save map
    for (int y = 0; y < m_tileMap.size(); y++)
    {
        for (int x = 0; x < m_tileMap.at(0).size(); x++)
        {
            const Sprite sprite = m_tileMap.at(y).at(x);
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

    for (int y = 0; y < m_tileMap.size(); y++)
    {
        for (int x = 0; x < m_tileMap.at(0).size(); x++)
        {
            m_tileMap.at(y).at(x).assetId = themeAssetId;
        }
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
    if (m_mapMenuOpen)
    {
        return;
    }

    if (m_entityMenuOpen)
    {
        return;
    }

    m_leftMouseHeld = true;
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

    m_mapMenuOpen = false;
    if (ImGui::Begin("Map Editor", NULL, window_flags))
    {
        m_mapMenuOpen = true;
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

    ImGui::SetNextWindowPos(ImVec2(0, 300), ImGuiCond_FirstUseEver);

    m_entityMenuOpen = false;
    if (ImGui::Begin("Entities Editor", NULL, window_flags))
    {
        m_entityMenuOpen = true;
        if (ImGui::CollapsingHeader("Components"))
        {
            std::vector<std::string> availableComponents =
                {"Animation",
                 "BoxCollider",
                 "CircleCollider",
                 "Health",
                 "Projectile",
                 "ProjectileEmitter",
                 "SceneSwitcher",
                 "Sprite",
                 "Tags",
                 "TextLabel",
                 "Transform",
                 "Velocity"};
            static int selectedAvailableComponentIndex = 0;

            ImGui::BeginGroup();
            ImGui::Text("Available Components");
            if (ImGui::BeginListBox("##Available Components"))
            {
                for (int n = 0; n < availableComponents.size(); n++)
                {
                    const bool isSelected = (selectedAvailableComponentIndex == n);
                    if (ImGui::Selectable(availableComponents.at(n).c_str(), isSelected))
                        selectedAvailableComponentIndex = n;

                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndListBox();
            }

            static std::vector<std::string> addedComponents =
                {"Animation",
                 "BoxCollider",
                 "Velocity"};
            static int selectedAddedComponentIndex = 0;

            if (ImGui::Button("Add Component"))
            {
                std::string componentName = availableComponents[selectedAvailableComponentIndex];
                addedComponents.push_back(componentName);
                selectedAddedComponentIndex = addedComponents.size() - 1;
                Logger::Info("Adding Component: " + componentName);
            }

            ImGui::EndGroup();
            ImGui::SameLine();
            ImGui::BeginGroup();

            ImGui::Text("Added Components");
            if (ImGui::BeginListBox("##Added Components"))
            {
                for (int n = 0; n < addedComponents.size(); n++)
                {
                    const bool isSelected = (selectedAddedComponentIndex == n);
                    if (ImGui::Selectable(addedComponents.at(n).c_str(), isSelected))
                        selectedAddedComponentIndex = n;

                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndListBox();
            }

            if (ImGui::Button("Delete Component"))
            {
                if (addedComponents.empty())
                {
                    Logger::Info("No components to delete, you simpleton");
                }
                else
                {
                    std::string componentName = addedComponents[selectedAddedComponentIndex];
                    Logger::Info("Deleting Component: " + componentName);
                    addedComponents.erase(addedComponents.begin() + selectedAddedComponentIndex);
                    if (selectedAddedComponentIndex > addedComponents.size() - 1)
                    {
                        selectedAddedComponentIndex = addedComponents.size() - 1;
                    }
                }
            }
            ImGui::EndGroup();
            ImGui::SameLine();
            ImGui::BeginGroup();
            ImGui::Text("Component Attributes");
            ImGui::EndGroup();
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
