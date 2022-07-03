#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include <fstream>
#include <algorithm>
#include "StardewBase.hpp"
#include "util/DropdownMenu.hpp"
#include "entities/PredefinedEntities.hpp"

class MapEditor : public StardewBase
{
private:
    // Predefined entities
    PredefinedEntities m_predefines = PredefinedEntities(*m_player);
    std::map<std::string, Entity*> *m_selectedEntities;
    std::map<std::string, Entity*>::iterator m_selectedEntityIterator;
    void SelectEntities(std::string sectionName);

    // Controller vars
    bool m_markedEntity = false;
    std::list<Entity*>::iterator m_markedEntityIterator;
    int m_selectedTileIndex = 1;
    Pixel m_mousePixel = {0, 0};
    enum
    {
        DRAW_TILE,
        DRAW_ENTITY,
        DELETE_ENTITY
    } m_action = DRAW_TILE;

    // Held keys
    bool m_mouseLeftHeld = false;
    bool m_mouseRightHeld = false;
    bool m_leftCtrlHeld = false;
    bool m_invertedScroll = false;
    bool m_mHeld = false;

    // Timer for showing tiles selection
    double m_renderSelection = 10.0;

    Pos m_selectedTile;
    Pixel PixelToTilePos(Pixel pixel);

    enum DropdownActivation
    {
        MissedClick,
        NoFunction,
        ToggleRenderHitbox,
        DrawTiles,
        DeleteEntity,
        PauseEntity,
        EntityNPC,
        EntityVegetation,
        EntityBuildings,
        EntityFurniture,
        EntityMisc
    };

    DropdownMenu m_dropdownMenu = DropdownMenu(
        {Element({160, 40}, "Draw Tiles", DrawTiles),
         Element({160, 40}, "Draw Entities     >", NoFunction,
                 {Element({100, 40}, "NPC", EntityNPC),
                  Element({130, 40}, "Vegetation", EntityVegetation),
                  Element({130, 40}, "Buildings", EntityBuildings),
                  Element({130, 40}, "Furniture", EntityFurniture),
                  Element({130, 40}, "Misc", EntityMisc)}),
         Element({160, 40}, "Delete Entities", DeleteEntity),
         Element({160, 40}, "Play/Pause Entities", PauseEntity),
         Element({160, 40}, "Render Hitbox", ToggleRenderHitbox),
         Element({160, 40}, "Nested menu  >", NoFunction,
                 {Element({100, 40}, "Nested 0", NoFunction),
                  Element({130, 40}, "Nested 1     >", NoFunction,
                          {Element({130, 40}, "Nested 1:0", NoFunction),
                           Element({130, 40}, "Nested 1:1", NoFunction)}),
                  Element({130, 40}, "Nested 2", NoFunction)}),
         Element({160, 40}, "Disappointment", NoFunction)});

    void HandleDropdownActivation(int id);

    // Controller funcs
    void HandleKeyEvents() override;
    void ScrollEntitySelectionUp();
    void ScrollEntitySelectionDown();
    void ScrollTileSelectionUp();
    void ScrollTileSelectionDown();
    void AddMapRow();
    void RemoveMapRow();
    void AddMapCol();
    void RemoveMapCol();
    void SaveMap();

public:
    void UpdateScene(double elapsedTime) override;
    void RenderScene(double elapsedTime) override;
    void LoadScene() override;
    void UnloadScene() override;
    using StardewBase::StardewBase;
};
#endif