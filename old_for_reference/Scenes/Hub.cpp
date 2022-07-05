
#include "Hub.hpp"

bool Hub::IsOnPos(Pos player, Pos teleport){
	return abs(player.x - teleport.x) <= 0.5 
		&& abs(player.y - teleport.y) <= 0.5;
}

void Hub::UpdateScene(double elapsedTime)
{
    // m_player is automatically rendered in base class.
    // Here you will update stuff specific to the scene environment.
    // For example if more enemies spawn during the scene, or if music changes.
	if (IsOnPos(m_player->GetPos(), m_grassTeleport)){
		m_sceneManager.QueueSceneChange("GRASS");
	}
}

void Hub::RenderScene(double elapsedTime)
{
    // m_player, m_map and m_entities are automatically rendered in base class
	//m_player->RenderHitbox(PosToPixel(m_player->GetPos()));
}

void Hub::LoadScene()
{
	g_sfx.StopMusic();   
	g_sfx.FreeAll();
	
	g_sfx.LoadMusic("chill-bass", "assets/sound/music/chill/chill-bass.wav");
	g_sfx.PlayMusic("chill-bass");

	ReadTilesFromFile("assets/maps/Hub.txt");

    m_player->SetPos({11, 4.5});
	m_player->SetSpriteDirection(Entity::DIR_DOWN);
	m_entitiesToCollisionCheck.push_back(m_player);
	

    m_entities.push_back(new Stalker(*m_player, "", {3.0, 5.0}, "assets/sprites/characters/foe/mysterious_blob.png", 3, {0, 0}, 4, 4));
	m_entities.back()->SetMapBorders(m_mapWidth, m_mapHeight);
	m_entitiesToCollisionCheck.push_back(m_entities.back());


	m_entities.push_back(new Entity("", m_grassTeleport, "assets/sprites/misc/wall_teleport.png", 0, {0, 0}, 1, 1, {0, -16}));
	m_entities.push_back(new Entity("", m_otherTeleport, "assets/sprites/misc/wall_teleport.png", 0, {0, 0}, 1, 1, {0, -16}));
	m_entities.push_back(new Entity("", m_anotherTeleport, "assets/sprites/misc/wall_teleport.png", 0, {0, 0}, 1, 1, {0, -16}));
	m_entities.push_back(new Entity("", m_anothererTeleport, "assets/sprites/misc/wall_teleport.png", 0, {0, 0}, 1, 1, {0, -16}));

	// Misc
	m_entities.push_back(new Entity("", {3.0, 3.0}, "assets/sprites/furniture/jukebox.png", {16, 16}, {0, 0}, 1, 1, {0, -8}));
	m_entities.push_back(new Entity("", {1.0, 1.3}, "assets/sprites/furniture/dartboard.png", 0));
	m_entities.push_back(new Entity("", {12.0, 3.0}, "assets/sprites/furniture/beer_fridge.png", {16, 20}, {0, 0}, 1, 1, {0, -8}));
	m_entities.push_back(new Entity("", {11.0, 1.0}, "assets/sprites/furniture/clock.png", 0));
	m_entities.push_back(new Entity("", {14.0, 1.0}, "assets/sprites/misc/rifle.png", 0));
	m_entities.push_back(new Entity("", {22.0, 6.0}, "assets/sprites/furniture/pool_table.png", {48, 8}));

	// Serving area
	m_entities.push_back(new Entity("", {7.0, 3.5}, "assets/sprites/furniture/table.png", 12));
	m_entities.push_back(new Entity("", {5.7, 3.8}, "assets/sprites/furniture/tiny_stool.png", 0));
	m_entities.push_back(new Entity("", {5.7, 3.3}, "assets/sprites/furniture/tiny_stool.png", 0));
	m_entities.push_back(new Entity("", {8.3, 3.8}, "assets/sprites/furniture/tiny_stool.png", 0));
	m_entities.push_back(new Entity("", {8.3, 3.3}, "assets/sprites/furniture/tiny_stool.png", 0));
	m_entities.push_back(new Entity("", {6.6, 4.4}, "assets/sprites/furniture/tiny_stool.png", 0));
	m_entities.push_back(new Entity("", {7.4, 4.4}, "assets/sprites/furniture/tiny_stool.png", 0));

	m_entities.push_back(new Entity("", {4.0, 7.5}, "assets/sprites/furniture/table.png", {12}));
	m_entities.push_back(new Entity("", {4.6, 6.9}, "assets/sprites/furniture/tiny_stool.png", 0));
	m_entities.push_back(new Entity("", {3.4, 6.9}, "assets/sprites/furniture/tiny_stool.png", 0));
	m_entities.push_back(new Entity("", {2.7, 7.8}, "assets/sprites/furniture/tiny_stool.png", 0));
	m_entities.push_back(new Entity("", {2.7, 7.3}, "assets/sprites/furniture/tiny_stool.png", 0));
	m_entities.push_back(new Entity("", {5.3, 7.8}, "assets/sprites/furniture/tiny_stool.png", 0));
	m_entities.push_back(new Entity("", {5.3, 7.3}, "assets/sprites/furniture/tiny_stool.png", 0));
	m_entities.push_back(new Entity("", {4.6, 8.4}, "assets/sprites/furniture/tiny_stool.png", 0));
	m_entities.push_back(new Entity("", {3.4, 8.4}, "assets/sprites/furniture/tiny_stool.png", 0));

	// Bar and stools
	m_entities.push_back(new Entity("", {9.5, 2.5}, "assets/sprites/furniture/bar_top1.png", {16, 16}));
	m_entities.push_back(new Entity("", {9.5, 3.5}, "assets/sprites/furniture/bar_top0.png", {16, 16}));
	m_entities.push_back(new Entity("", {9.5, 4.5}, "assets/sprites/furniture/bar_top1.png", {16, 16}));
	m_entities.push_back(new Entity("", {9.5, 5.5}, "assets/sprites/furniture/bar_top0.png", {16, 16}));
	m_entities.push_back(new Entity("", {9.5, 6.0}, "assets/sprites/furniture/bar_middle.png", {16, 20}));
	m_entities.push_back(new Entity("", {10.5, 6.0}, "assets/sprites/furniture/bar_middle.png",{16, 20}));
	m_entities.push_back(new Entity("", {11.5, 6.0}, "assets/sprites/furniture/bar_middle.png",{16, 20}));
	m_entities.push_back(new Entity("", {11.0, 7.3}, "assets/sprites/furniture/bar_stool.png", {16, 16}, {0, 0}, 1, 1, {0, -4}));
	m_entities.push_back(new Entity("", {12.5, 6.0}, "assets/sprites/furniture/bar_middle.png", {16, 20}));
	m_entities.push_back(new Entity("", {13.5, 6.0}, "assets/sprites/furniture/bar_middle.png", {16, 20}));
	m_entities.push_back(new Entity("", {13.0, 7.3}, "assets/sprites/furniture/bar_stool.png", {16, 16}, {0, 0}, 1, 1, {0, -4}));
	m_entities.push_back(new Entity("", {14.5, 6.0}, "assets/sprites/furniture/bar_middle.png", {16, 20}));
	m_entities.push_back(new Entity("", {15.5, 6.0}, "assets/sprites/furniture/bar_middle.png", {16, 20}));
	m_entities.push_back(new Entity("", {15.5, 5.0}, "assets/sprites/furniture/bar_top0.png", {16, 16}));

}


void Hub::UnloadScene()
{
    // Entities and Tiles are automatically cleaned in base class.
    // You have to clean the sounds that you are leaving behind.
    g_sfx.FreeAll();
}
