#ifndef SCENE_H
#define SCENE_H

class SceneManager;
class Scene
{
public:
	SceneManager &m_sceneManager;
	virtual void Update(double elapsedTime) = 0;
	virtual void RenderGraphics(double elapsedTime) = 0;
	virtual void Load() = 0;   // Load sprites and audio needed for the scene
	virtual void Unload() = 0; // Unload sprites and audio to avoid memory leaks
	void Cycle(double elapsedTime);
	Scene(SceneManager &sceneManager);
};
#endif // SCENE_H