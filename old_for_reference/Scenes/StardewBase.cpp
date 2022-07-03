#include "StardewBase.hpp"

bool StardewBase::Update(double elapsedTime)
{
	//Run Systems

	UpdateScene(elapsedTime);
	return true;
}

void StardewBase::RenderGraphics(double elapsedTime)
{
	g_gfx.ResetRenderArea();

	//Update RenderSystems

	RenderScene(elapsedTime);

	g_gfx.RenderBuffer();
}


void StardewBase::PrintFPS(double elapsedTime)
{
	m_frameCounter++;
	m_fpsTimer -= elapsedTime;
	if (m_fpsTimer < 0.0)
	{
		std::cout << m_frameCounter << " fps\n";
		m_frameCounter = 0;
		m_fpsTimer = 1.0;
	}
}

void StardewBase::Load()
{
	LoadScene();
}

void StardewBase::Unload()
{
	UnloadScene();
}

StardewBase::StardewBase(SceneManager &sceneManager)
	: Scene(sceneManager)
{
}