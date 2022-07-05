#ifndef HUB_H
#define HUB_H

#include "StardewBase.hpp"
#include "util/PixelPos.hpp"

class Hub : public StardewBase 
{
private:
    Pos m_grassTeleport = { 18.5, 3.0 };
    Pos m_otherTeleport = { 20.5, 3.0 };
    Pos m_anotherTeleport = { 22.5, 3.0 };
    Pos m_anothererTeleport = { 24.5, 3.0 };

    bool IsOnPos(Pos player, Pos teleport);

public:
    void UpdateScene(double elapsedTime) override;
	void RenderScene(double elapsedTime) override;
	void LoadScene() override;
	void UnloadScene() override;
    using StardewBase::StardewBase;
};
#endif