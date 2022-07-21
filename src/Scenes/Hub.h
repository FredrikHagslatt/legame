#ifndef HUB_H
#define HUB_H

#include "Scenes/Stardew.h"

class Hub : public Stardew
{
public:
	void UpdateScene(const double elapsedTime) override;
	void RenderScene(const double elapsedTime) override;
	void LoadScene() override;
	void UnloadScene() override;
	using Stardew::Stardew;
};

#endif