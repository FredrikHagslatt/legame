#include "SceneManager.h"

void SceneManager::OnSceneSwitchEvent(const SceneSwitchEvent event)
{
	Logger::Info("[Scenemanager] Received SceneSwitchEvent: " + event.sceneName);
	QueueSceneChange(event.sceneName);
}

void SceneManager::QueueSceneChange(std::string sceneName)
{
	m_queuedScene = sceneName;
}

void SceneManager::ChangeScene(std::string sceneName)
{
	if (m_scenes.count(sceneName) != 1)
	{
		Logger::Error("[Scenemanager] Scene '" + sceneName + "' does not exist in SceneManager");
		return;
	}

	if (m_currentScene)
	{
		m_currentScene->Unload();
	}
	Logger::Info("Changing scene to " + sceneName);
	m_currentScene = m_scenes.at(sceneName);
	m_currentScene->Load();
}

void SceneManager::AddScene(std::string sceneName, std::shared_ptr<Scene> scene)
{
	m_scenes.insert(std::pair<std::string, std::shared_ptr<Scene>>(sceneName, scene));
}

bool SceneManager::Cycle(double elapsedTime)
{
	m_currentScene->Cycle(elapsedTime);

	if (!m_queuedScene.empty())
	{
		ChangeScene(m_queuedScene);
		m_queuedScene = "";
	}
	return true;
}

SceneManager::SceneManager()
{
	m_currentScene = nullptr;
}