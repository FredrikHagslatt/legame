#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>
#include <unordered_map>
#include "Scene.h"

class SceneManager
{
private:
	Scene *m_currentScene;
	std::unordered_map<std::string, Scene *> m_scenes;
	std::string m_queuedScene = "";

public:
	void QueueSceneChange(std::string name);
	void ChangeScene(std::string name);
	bool Cycle(double elapsedTime);
	void AddScene(std::string name, Scene *scene);
	SceneManager();
	//~SceneManager();
};
#endif // SCENE_MANAGER_H