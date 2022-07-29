#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "Scenes/Stardew.h"
#include "Types.h"

class MapEditor : public Stardew
{
private:
	//    LoadMap("assets/tilemaps/ground_tiles.png", "assets/tilemaps/hub.map");
	std::string spritesheet = "assets/tilemaps/ground_tiles.png";
	vec2i selectedTile = vec2i(0);

	bool showTileSelector = false;

	int mapNumCols = 1;
	int mapNumRows = 1;
	int queuedMapNumCols = 1;
	int queuedMapNumRows = 1;

	void UpdateMapSize();
	void IncreaseMapWidth(int newWidth);
	void DecreaseMapWidth(int newWidth);
	void IncreaseMapHeight(int newHeight);
	void DecreaseMapHeight(int newHeight);

public:
	void UpdateScene(const double elapsedTime) override;
	void RenderScene(const double elapsedTime) override;
	void LoadScene() override;
	void UnloadScene() override;
	using Stardew::Stardew;
};

#endif