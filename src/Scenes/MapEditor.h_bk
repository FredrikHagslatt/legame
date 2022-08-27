#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "Types.h"
#include "Scenes/Stardew.h"
#include "Events/MouseMotionEvent.h"
#include "Events/MouseButtonPressedEvent.h"
#include "Events/MouseButtonReleasedEvent.h"

class MapEditor : public Stardew
{
private:
	std::string m_theme = "assets/tilemaps/themes/ground_tiles.png";
	vec2i m_selectedSubSprite = vec2i(0);
	std::unique_ptr<entt::entity> m_selectedTile;
	entt::entity m_tileBrush;

	bool m_showTileSelector = false;
	bool m_leftMouseHeld = false;

	int m_mapNumCols = 1;
	int m_mapNumRows = 1;
	int m_queuedMapNumCols = 1;
	int m_queuedMapNumRows = 1;

	void UpdateMapSize();
	void IncreaseMapWidth(int newWidth);
	void DecreaseMapWidth(int newWidth);
	void IncreaseMapHeight(int newHeight);
	void DecreaseMapHeight(int newHeight);
	void SelectTile(const MouseMotionEvent &event);
	void PlaceTile();
	void SaveMap(const std::string filename);
	std::vector<std::string> GetThemes();
	void SelectTheme(std::string themePath);

	void OnMouseMotionEvent(const MouseMotionEvent &event);
	void OnMouseButtonPressedEvent(const MouseButtonPressedEvent &event);
	void OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent &event);

public:
	void UpdateScene(const double elapsedTime) override;
	void RenderScene(const double elapsedTime) override;
	void LoadScene() override;
	void UnloadScene() override;
	using Stardew::Stardew;
};

#endif