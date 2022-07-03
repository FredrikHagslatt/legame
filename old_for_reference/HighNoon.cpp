#include "HighNoon.hpp"
#include "Constants.hpp"

	HighNoon::HighNoon()
	: m_sceneManager(){
		m_player = new Player("Player", {0, 0}, "assets/sprites/characters/friend/Dinah.png", 4, {0, 0}, 4, 5, {0, -8});
		m_sceneManager.AddScene("MENU", new MenuRoot(m_sceneManager));
		m_sceneManager.AddScene("HUB", new Hub(m_sceneManager, m_player));
		m_sceneManager.AddScene("GRASS", new StardewTemplate(m_sceneManager, m_player));
		m_sceneManager.AddScene("MAPEDITOR", new MapEditor(m_sceneManager, m_player));
		//sceneManager->AddScene(CREDITS, new CreditsScene(sceneManager));
		m_sceneManager.ChangeScene("MENU");
		m_now_time = SDL_GetPerformanceCounter(); 
	}

	HighNoon::~HighNoon(){}

	bool HighNoon::GameCycle(){
		
		uint64_t last_time = m_now_time; 
		m_now_time = SDL_GetPerformanceCounter(); 
		double elapsedTime = static_cast<double>( (m_now_time - last_time) / static_cast<double>(SDL_GetPerformanceFrequency()) );
		return m_sceneManager.Cycle(elapsedTime);
	}