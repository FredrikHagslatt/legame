#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>
#include <unordered_map>
#include "Scene.h"
#include "Events/SceneSwitchEvent.h"
#include "Logger/Logger.h"

class SceneManager
{
private:
	std::shared_ptr<Scene> m_currentScene;
	// Scene *m_currentScene;

	std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;
	// std::unordered_map<std::string, Scene *> m_scenes;

	std::string m_queuedScene = "";

public:
	void OnSceneSwitchEvent(const SceneSwitchEvent event);
	void QueueSceneChange(std::string name);
	void ChangeScene(std::string name);
	bool Cycle(double elapsedTime);
	void AddScene(std::string name, std::shared_ptr<Scene> scene);
	SceneManager();
	//~SceneManager();
};
#endif // SCENE_MANAGER_H