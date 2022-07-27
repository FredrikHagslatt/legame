#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "Scenes/Stardew.h"

class MapEditor : public Stardew
{
private:
	int queuedMapWidth = 5;
	int queuedMapHeight = 5;

	void UpdateMapSize();
	void IncreaseMapWidth(int oldWidth, int newWidth);
	void DecreaseMapWidth(int newWidth);
	void IncreaseMapHeight(int oldHeight, int newHeight);
	void DecreaseMapHeight(int newHeight);

public:
	void UpdateScene(const double elapsedTime) override;
	void RenderScene(const double elapsedTime) override;
	void LoadScene() override;
	void UnloadScene() override;
	using Stardew::Stardew;
};

#endif