#include "SceneManager.h"

void SceneManager::OnSceneSwitchEvent(const SceneSwitchEvent event)
{
	Logger::Info("[Scenemanager] Received SceneSwitchEvent: " + event.scene);
	QueueSceneChange(event.scene);
}

void SceneManager::QueueSceneChange(std::string name)
{
	m_queuedScene = name;
}

void SceneManager::ChangeScene(std::string name)
{
	if (m_scenes.count(name) != 1)
	{
		Logger::Error("[Scenemanager] Scene '" + name + "' does not exist in SceneManager");
		return;
	}

	if (m_currentScene)
	{
		m_currentScene->Unload();
	}
	Logger::Info("Changing scene to " + name);
	m_currentScene = m_scenes.at(name);
	m_currentScene->Load();
}

void SceneManager::AddScene(std::string name, Scene *scene)
{
	m_scenes.insert(std::pair<std::string, Scene *>(name, scene));
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