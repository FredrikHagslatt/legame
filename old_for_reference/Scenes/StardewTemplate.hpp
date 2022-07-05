#ifndef STARDEW_TEMPLATE_H
#define STARDEW_TEMPLATE_H

#include "StardewBase.hpp"

class StardewTemplate : public StardewBase 
{
    public:
    void UpdateScene(double elapsedTime) override;
	void RenderScene(double elapsedTime) override;
	void LoadScene() override;
	void UnloadScene() override;
    using StardewBase::StardewBase;
};
#endif