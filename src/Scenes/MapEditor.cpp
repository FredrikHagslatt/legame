#include "MapEditor.h"
#include "Constants.h"
#include "DevTools/DevTools.h"

void MapEditor::UpdateMapSize()
{
    if (queuedMapNumCols > mapNumCols)
    {
        IncreaseMapWidth(queuedMapNumCols);
    }
    else if (queuedMapNumCols < mapNumCols)
    {
        DecreaseMapWidth(queuedMapNumCols);
    }

    if (queuedMapNumRows > mapNumRows)
    {
        IncreaseMapHeight(queuedMapNumRows);
    }
    else if (queuedMapNumRows < mapNumRows)
    {
        DecreaseMapHeight(queuedMapNumRows);
    }

    mapWidth = mapNumCols * TILESIZE * SCALE;
    mapHeight = mapNumRows * TILESIZE * SCALE;
}

void MapEditor::IncreaseMapWidth(int newNumCols)
{
    for (int y = 0; y < mapNumRows; y++)
    {
        for (int x = mapNumCols; x < newNumCols; x++)
        {
            const auto tile = m_registry->create();
            m_registry->emplace<Tile_Tag>(tile);
            m_registry->emplace<Transform>(tile, vec2f(x * SCALE * TILESIZE, y * SCALE * TILESIZE));
            m_registry->emplace<Sprite>(tile, spritesheet, TILESIZE, TILESIZE, 0, false, 0, 0);
        }
    }
    mapNumCols = newNumCols;
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
    mapNumCols = newNumCols;
}

void MapEditor::IncreaseMapHeight(int newNumRows)
{
    for (int x = 0; x < mapNumCols; x++)
    {
        for (int y = mapNumRows; y < newNumRows; y++)
        {
            const auto tile = m_registry->create();
            m_registry->emplace<Tile_Tag>(tile);
            m_registry->emplace<Transform>(tile, vec2f(x * SCALE * TILESIZE, y * SCALE * TILESIZE));
            m_registry->emplace<Sprite>(tile, spritesheet, TILESIZE, TILESIZE, 0, false, 0, 0);
        }
    }
    mapNumRows = newNumRows;
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
    mapNumRows = newNumRows;
}

void MapEditor::SelectTile()
{
    int mouseX, mouseY;
    Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);

    auto view = m_registry->view<Tile_Tag, Transform>();

    for (auto entity : view)
    {
        const auto transform = view.get<Transform>(entity);
        if (mouseX >= transform.position.x - camera.x && mouseX <= transform.position.x - camera.x + TILESIZE * SCALE && mouseY >= transform.position.y - camera.y && mouseY <= transform.position.y - camera.y + TILESIZE * SCALE)
        {
            Logger::Info("One tile");
        }
    }
}

void MapEditor::UpdateScene(const double elapsedTime)
{
    queuedMapNumCols = std::max(1, queuedMapNumCols);
    queuedMapNumRows = std::max(1, queuedMapNumRows);

    UpdateMapSize();
    SelectTile();
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

        if (ImGui::CollapsingHeader("Mapsize"))
        {
            ImGui::InputInt("Number of columns", &queuedMapNumCols);
            ImGui::InputInt("Number of rows", &queuedMapNumRows);
        }

        if (ImGui::CollapsingHeader("Tileselector"))
        {
            SDL_Texture *texture = m_assetStore->GetTexture("assets/tilemaps/ground_tiles.png");
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
                        selectedSubSprite = vec2i(x, y);
                        Logger::Info("Selecting sub sprite " + selectedSubSprite.string());
                    }
                    ImGui::PopID();
                    ImGui::SameLine();
                }
                ImGui::NewLine();
            }
        }
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void MapEditor::LoadScene()
{
    LoadMap("assets/tilemaps/ground_tiles.png", "assets/tilemaps/map_editor.map");

    queuedMapNumCols = mapWidth / TILESIZE / SCALE;
    queuedMapNumRows = mapHeight / TILESIZE / SCALE;
    mapNumCols = queuedMapNumCols;
    mapNumRows = queuedMapNumRows;

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
}

void MapEditor::UnloadScene()
{
}
