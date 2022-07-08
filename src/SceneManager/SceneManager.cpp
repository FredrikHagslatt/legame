#include "SceneManager.h"
#include "Game/Game.h"

void SceneManager::OnSceneSwitchEvent(const SceneSwitchEvent event)
{
	if (event.managerId == id)
	{
		Logger::Info("[Scenemanager] Manager with id: " + id + ", Received SceneSwitchEvent: " + event.sceneName);
		QueueSceneChange(event.sceneName);
	}
	else
	{
		Logger::Info(id + " - " + event.managerId);
	}
}

void SceneManager::QueueSceneChange(const std::string sceneName)
{
	m_queuedScene = sceneName;
}

void SceneManager::ChangeScene(const std::string sceneName)
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
	Logger::Info("[SceneManager] Changing scene to '" + sceneName + "'");
	m_currentScene = m_scenes.at(sceneName);
	m_currentScene->Load();
}

void SceneManager::AddScene(const std::string sceneName, const std::shared_ptr<Scene> scene)
{
	m_scenes.insert(std::pair<std::string, std::shared_ptr<Scene>>(sceneName, scene));
}

bool SceneManager::Cycle(const double elapsedTime)
{
	if (!m_queuedScene.empty())
	{
		ChangeScene(m_queuedScene);
		m_queuedScene = "";
	}
	m_currentScene->Cycle(elapsedTime);

	return true;
}

void SceneManager::ClearScenes()
{
	m_currentScene = nullptr;
	m_scenes.clear(); // I fukkin hope this removes the scenes. It probably does..
}

SceneManager::SceneManager(const std::string id)
	: id(id)
{
	m_currentScene = nullptr;
}