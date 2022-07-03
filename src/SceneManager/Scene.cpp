#include "Scene.h"

void Scene::Cycle(double elapsedTime) {
	Update(elapsedTime);
	RenderGraphics(elapsedTime);
}

Scene::Scene(SceneManager& sceneManager)
	: m_sceneManager(sceneManager)
{}