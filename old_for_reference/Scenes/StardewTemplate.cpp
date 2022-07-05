
#include "StardewTemplate.hpp"

void StardewTemplate::UpdateScene(double elapsedTime)
{
    // m_player is automatically rendered in base class.
    // Here you will update stuff specific to the scene environment.
    // For example if more enemies spawn during the scene, or if music changes.
}

void StardewTemplate::RenderScene(double elapsedTime)
{
    // m_map and m_enteties are automatically rendered in base class
}

void StardewTemplate::LoadScene()
{
	g_sfx.LoadMusic("chill-bass", "assets/sound/music/chill/chill-bass.wav");
	g_sfx.PlayMusic("chill-bass");

	ReadTilesFromFile("assets/maps/GrassTest.txt");

    m_player->SetPos({float(m_mapWidth) / 2, float(m_mapHeight) / 2});


	for (int i = 0; i < m_mapWidth; i++){
		for (int j = 0; j < m_mapHeight; j++){
			if (i < 17 || i > 19 || j < 4 || j > 13){
				if (rand() % 10 > 2){
					m_entities.push_back(new Entity("", {float(i), float(j)}, "assets/sprites/vegetation/trees/fir.png", 3, {0, 0}, 1, 1, {0, -21}));
				}
			}
		}
	}

	Entity* spike = new Entity("",{18.4, 5}, "assets/sprites/characters/friend/Spike.png", 4, {0, 0}, 4, 5, {0, -8});
	spike->SetSpriteDirection(Entity::DIR_DOWN);
	m_entities.push_back(spike);
	m_entities.push_back(new Entity("", {18, 4.9}, "assets/sprites/furniture/bench.png", {20, 8}));
}

void StardewTemplate::UnloadScene()
{
    // Entitys and Tiles are automatically cleaned in base class.
    // You have to clean the sounds that you are leaving behind.
    g_sfx.FreeAll();
}
