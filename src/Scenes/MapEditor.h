#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "Scenes/Stardew.h"

class MapEditor : public Stardew
{
public:
	void UpdateScene(const double elapsedTime) override;
	void RenderScene(const double elapsedTime) override;
	void LoadScene() override;
	void UnloadScene() override;
	using Stardew::Stardew;
};

#endif