#include "SceneManager.h"


void SceneManager::QueueSceneChange(std::string name)
{
	m_queuedScene = name;
}

void SceneManager::ChangeScene(std::string name)
{
	if (m_currentScene)
	{
		m_currentScene->Unload();
	}
	m_currentScene = m_scenes.at(name);
	m_currentScene->Load();
}

void SceneManager::AddScene(std::string name, Scene *scene)
{
	m_scenes.insert( std::pair<std::string, Scene*>(name, scene) );
}

bool SceneManager::Cycle(double elapsedTime)
{
	if(m_queuedScene.empty()){
		m_currentScene->Cycle(elapsedTime);
	}else{
		ChangeScene(m_queuedScene);
		m_queuedScene = "";
	}
	return true;
}

SceneManager::SceneManager()
{
	m_currentScene = nullptr;
}