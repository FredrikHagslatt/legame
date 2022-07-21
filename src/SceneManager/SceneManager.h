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
	std::string id;
	std::shared_ptr<Scene> m_currentScene;
	std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;
	std::string m_queuedScene = "";
	void ChangeScene(const std::string sceneName);

public:
	void OnSceneSwitchEvent(const SceneSwitchEvent event);
	void QueueSceneChange(const std::string sceneName);
	void Update(const double elapsedTime);
	void RenderGraphics(const double elapsedTime);
	void AddScene(const std::string sceneName, const std::shared_ptr<Scene> scene);
	void ClearScenes();
	SceneManager(const std::string id);

	//~SceneManager();
};
#endif // SCENE_MANAGER_H