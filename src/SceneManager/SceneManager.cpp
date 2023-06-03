#include "SceneManager.h"
#include "Game/Game.h"

void SceneManager::OnSceneSwitchEvent(const SceneSwitchEvent event)
{
	if (event.managerId == id)
	{
		Logger::Info("[Scenemanager] Manager with id: " + id + ", Received SceneSwitchEvent: " + event.sceneName + ", " + event.level);
		QueueSceneChange(event.sceneName, event.level);
	}
	else
	{
		Logger::Info(id + " - " + event.managerId);
	}
}

void SceneManager::QueueSceneChange(const std::string sceneName, const std::string level)
{
	m_queuedScene = sceneName;
	m_queuedLevel = level;
}

void SceneManager::ChangeScene(const std::string sceneName, const std::string level)
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
	m_currentScene->Load(level);
}

void SceneManager::AddScene(const std::string sceneName, const std::shared_ptr<Scene> scene)
{
	m_scenes.insert(std::pair<std::string, std::shared_ptr<Scene>>(sceneName, scene));
}

void SceneManager::Update(const double elapsedTime)
{
	if (!m_queuedScene.empty())
	{
		ChangeScene(m_queuedScene, m_queuedLevel);
		m_queuedScene = "";
		m_queuedLevel = "";
	}
	m_currentScene->Update(elapsedTime);
}

void SceneManager::RenderGraphics(const double elapsedTime)
{
	m_currentScene->RenderGraphics(elapsedTime);
}

void SceneManager::ClearScenes()
{
	m_currentScene->Unload();
	m_currentScene = nullptr;
	m_scenes.clear(); // I fukkin hope this removes the scenes. It probably does..
}

SceneManager::SceneManager(const std::string id)
	: id(id)
{
	m_currentScene = nullptr;
}