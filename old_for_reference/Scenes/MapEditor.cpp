#include "MapEditor.hpp"
#include <iostream>

Pixel MapEditor::PixelToTilePos(Pixel pixel)
{
	std::pair<int, int> pos;
	if (m_mapWidth > CAMWIDTH)
	{
		pos.first = int((float(pixel.x - SCREENWIDTH / 2) / (SCALE * TILESIZE)) + m_camera.x);
	}
	else
	{
		pos.first = int((float(pixel.x - SCREENWIDTH / 2) / (SCALE * TILESIZE)) + m_mapWidth / 2);
	}

	if (m_mapHeight > CAMHEIGHT)
	{
		pos.second = int((float(pixel.y - SCREENHEIGHT / 2) / (SCALE * TILESIZE)) + m_camera.y);
	}
	else
	{
		pos.second = int((float(pixel.y - SCREENHEIGHT / 2) / (SCALE * TILESIZE)) + m_mapHeight / 2);
	}

	// Stay on map. Borderchecks.
	pos.first = std::max(0, pos.first);
	pos.first = std::min(pos.first, m_mapWidth - 1);
	pos.second = std::max(0, pos.second);
	pos.second = std::min(pos.second, m_mapHeight - 1);

	return {pos.first, pos.second};
}

void MapEditor::ScrollEntitySelectionDown()
{
	m_renderSelection = 0.0;
	if (m_selectedEntityIterator != --m_selectedEntities->end())
	{
		m_selectedEntityIterator++;
	}
}

void MapEditor::ScrollEntitySelectionUp()
{
	m_renderSelection = 0.0;
	if (m_selectedEntityIterator != m_selectedEntities->begin())
	{
		m_selectedEntityIterator--;
	}
}

void MapEditor::ScrollTileSelectionDown()
{
	m_renderSelection = 0.0;
	if (m_selectedTileIndex < m_tiles.size() - 1)
	{
		m_selectedTileIndex++;
	}
}

void MapEditor::ScrollTileSelectionUp()
{
	m_renderSelection = 0.0;
	if (m_selectedTileIndex > 0)
	{
		m_selectedTileIndex--;
	}
}

void MapEditor::AddMapRow()
{
	m_map.push_back(m_map.back());
	m_mapHeight = m_map.size();
	m_player->SetMapBorders(m_mapWidth, m_mapHeight);
}

void MapEditor::RemoveMapRow()
{
	m_map.pop_back();
	m_mapHeight = m_map.size();
	m_player->SetMapBorders(m_mapWidth, m_mapHeight);
}

void MapEditor::AddMapCol()
{
	for (int i = 0; i < m_map.size(); i++)
	{
		m_map[i].push_back(m_map[i].back());
	}
	m_mapWidth = m_map[0].size();
	m_player->SetMapBorders(m_mapWidth, m_mapHeight);
}

void MapEditor::RemoveMapCol()
{
	for (int i = 0; i < m_map.size(); i++)
	{
		m_map[i].pop_back();
	}
	m_mapWidth = m_map[0].size();
	m_player->SetMapBorders(m_mapWidth, m_mapHeight);
}

void MapEditor::SaveMap()
{
	std::ofstream mapFile;
	mapFile.open("Generated_Map.txt");

	// Filter out unused tiles
	std::vector<Tile *> usedTiles;
	for (auto &row : m_map)
	{
		for (auto &element : row)
		{
			if (std::find(usedTiles.begin(), usedTiles.end(), element) == usedTiles.end())
			{
				usedTiles.push_back(element);
			}
		}
	}

	// Save tiles
	mapFile << "# TILES #\n";

	for (auto &tile : usedTiles)
	{
		mapFile << tile->GetSpritePath() << ';' << tile->GetStateOfMatter() << '\n';
	}

	// Delimiter
	mapFile << "# MAP #\n";

	// Map index of tiles to avoid a search for every grid pos.
	std::unordered_map<Tile *, int> tilesIndexes;
	for (int i = 0; i < usedTiles.size(); i++)
	{
		tilesIndexes.insert({usedTiles.at(i), i});
	}

	// Save grid
	for (auto &row : m_map)
	{
		for (auto &element : row)
		{
			mapFile << tilesIndexes.at(element) << ',';
		}
		mapFile << '\n';
	}

	mapFile << "# ENTITIES #\n";

	for (auto &entity : m_entities)
	{
		mapFile << entity->GetUid() << ';' << entity->GetPos().x << ';' << entity->GetPos().y << '\n';
	}
	mapFile.close();
}

void MapEditor::SelectEntities(std::string sectionName)
{
	if (m_predefines.m_collection.count(sectionName))
	{ // If section name exists
		if (m_predefines.m_collection.at(sectionName).size())
		{ // If section has entities
			m_selectedEntities = &m_predefines.m_collection.at(sectionName);
			m_selectedEntityIterator = m_selectedEntities->begin();
			m_action = DRAW_ENTITY;
		}
	}
}

void MapEditor::HandleDropdownActivation(int id)
{
	switch (id)
	{
	case ToggleRenderHitbox:
		m_renderHitboxes = !m_renderHitboxes;
	case DrawTiles:
		m_selectedTileIndex = 0;
		m_action = DRAW_TILE;
		break;
	case DeleteEntity:
		m_action = DELETE_ENTITY;
		break;
	case PauseEntity:
		m_pauseEntities = !m_pauseEntities;
		break;
	case EntityNPC:
		SelectEntities("NPC");
		break;
	case EntityVegetation:
		SelectEntities("vegetation");
		break;
	case EntityBuildings:
		SelectEntities("buildings");
		break;
	case EntityFurniture:
		SelectEntities("furniture");
		break;
	case EntityMisc:
		SelectEntities("misc");
		break;
	}
}

void MapEditor::HandleKeyEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				m_sceneManager.QueueSceneChange("MENU");
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_I)
			{
				m_invertedScroll = !m_invertedScroll;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_SLASH // Slash on murican is minus on Nordic
					 || event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS)
			{
				if (m_invertedScroll)
				{
					if (m_action == DRAW_TILE)
					{
						ScrollTileSelectionUp();
					}
					else if (m_action == DRAW_ENTITY)
					{
						ScrollEntitySelectionUp();
					}
				}
				else
				{
					if (m_action == DRAW_TILE)
					{
						ScrollTileSelectionDown();
					}
					else if (m_action == DRAW_ENTITY)
					{
						ScrollEntitySelectionDown();
					}
				}
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_MINUS // Minus on murican is plus on Nordic
					 || event.key.keysym.scancode == SDL_SCANCODE_KP_PLUS)
			{
				if (m_invertedScroll)
				{
					if (m_action == DRAW_TILE)
					{
						ScrollTileSelectionDown();
					}
					else if (m_action == DRAW_ENTITY)
					{
						ScrollEntitySelectionDown();
					}
				}
				else
				{
					if (m_action == DRAW_TILE)
					{
						ScrollTileSelectionUp();
					}
					else if (m_action == DRAW_ENTITY)
					{
						ScrollEntitySelectionUp();
					}
				}
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_S && m_leftCtrlHeld)
			{
				SaveMap();
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_LCTRL)
			{
				m_leftCtrlHeld = true;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_M)
			{
				m_mHeld = true;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_UP && m_mHeld)
			{
				RemoveMapRow();
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN && m_mHeld)
			{
				AddMapRow();
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT && m_mHeld)
			{
				RemoveMapCol();
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT && m_mHeld)
			{
				AddMapCol();
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_LCTRL)
			{
				m_leftCtrlHeld = false;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_M)
			{
				m_mHeld = false;
			}
		}

		else if (event.type == SDL_MOUSEMOTION)
		{ // Move mouse, calc position
			SDL_GetMouseState(&m_mousePixel.x, &m_mousePixel.y);
			m_dropdownMenu.SetMousePixel(m_mousePixel);
			m_selectedTile = PixelToPos(m_mousePixel).floor();

			// Limit m_selectedTile to map.
			m_selectedTile.x = float(std::min(int(m_selectedTile.x), m_mapWidth - 1));
			m_selectedTile.y = float(std::min(int(m_selectedTile.y), m_mapHeight - 1));
			m_selectedTile.x = float(std::max(int(m_selectedTile.x), 0));
			m_selectedTile.y = float(std::max(int(m_selectedTile.y), 0));
		}

		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{

				if (m_dropdownMenu.Expanded())
				{
					HandleDropdownActivation(m_dropdownMenu.Click(m_mousePixel).second);
				}
				else if(m_action == DRAW_TILE)
				{
					m_mouseLeftHeld = true;
				}
				else if (m_action == DRAW_ENTITY)
				{
					m_selectedEntityIterator->second->SetPos(PixelToPos(m_mousePixel));
					m_entities.push_back(m_selectedEntityIterator->second->Clone());
				}
				else if (m_action == DELETE_ENTITY)
				{
					if (!m_entities.empty() && m_markedEntity)
					{
						m_entities.erase(m_markedEntityIterator);
					}
				}
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{ // Dropdown Menu
				m_dropdownMenu.Expand(m_mousePixel);
			}
		}

		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				m_mouseLeftHeld = false;
			}
		}

		else if (event.type == SDL_MOUSEWHEEL)
		{ // Switch Tile to place
			m_renderSelection = 0.0;
			if (event.wheel.y > 0)
			{
				if (m_invertedScroll)
				{
					if (m_action == DRAW_TILE)
					{
						ScrollTileSelectionDown();
					}
					else if (m_action == DRAW_ENTITY)
					{
						ScrollEntitySelectionDown();
					}
				}
				else
				{
					if (m_action == DRAW_TILE)
					{
						ScrollTileSelectionUp();
					}
					else if (m_action == DRAW_ENTITY)
					{
						ScrollEntitySelectionUp();
					}
				}
			}
			else if (event.wheel.y < 0)
			{
				if (m_invertedScroll)
				{
					if (m_action == DRAW_TILE)
					{
						ScrollTileSelectionUp();
					}
					else if (m_action == DRAW_ENTITY)
					{
						ScrollEntitySelectionUp();
					}
				}
				else
				{
					if (m_action == DRAW_TILE)
					{
						ScrollTileSelectionDown();
					}
					else if (m_action == DRAW_ENTITY)
					{
						ScrollEntitySelectionDown();
					}
				}
			}
		}

		if ((m_leftCtrlHeld || m_mHeld) == false)
		{
			m_player->Controller(event);
		}
	}
}

void MapEditor::UpdateScene(double elapsedTime)
{

	if (m_action == DELETE_ENTITY && !m_entities.empty())
	{
		// Set first to have something to compare too
		Pos mousePos = PixelToPos(m_mousePixel);
		float closestDistance = 1000000; // Very long distance. Even longer than Sigge is wide.

		// Calculate Entity closes to mouse
		for (std::list<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
		{
			(*it)->SetColorMod(255, 255, 255);
			float distance = ((*it)->GetPos() - mousePos).magnitude();
			if (distance < closestDistance)
			{
				m_markedEntityIterator = it;
				closestDistance = distance;
			}
		}
		if (((*m_markedEntityIterator)->GetPos() - mousePos).magnitude() < 2.0f)
		{
			m_markedEntity = true;
			(*m_markedEntityIterator)->SetColorMod(255, 100, 100);
		}
		else
		{
			m_markedEntity = false;
		}
	}

	if (m_action == DRAW_TILE && m_mouseLeftHeld)
	{
		m_map[m_selectedTile.y][m_selectedTile.x] = m_tiles.at(m_selectedTileIndex);
	}
}

void MapEditor::RenderScene(double elapsedTime)
{
	Pixel pixel = PosToPixel(m_selectedTile);

	if (m_action == DRAW_TILE)
	{
		if (m_renderSelection < 1.0) // If scrolled recently
		{
			m_renderSelection += elapsedTime;
			Tile background("assets/sprites/misc/black_frame16x16.png");

			for (int i = 0; i < m_tiles.size(); i++)
			{ // Draw available tiles
				m_tiles.at(i)->Render({pixel.x, pixel.y + (i - m_selectedTileIndex) * (TILESIZE * SCALE)});
				background.Render({pixel.x, pixel.y + (i - m_selectedTileIndex) * (TILESIZE * SCALE)});
			}
		}
		m_tiles.at(m_selectedTileIndex)->Render(pixel);
		// Draw pretty frame to know where you are painting
		Tile borderFrame("assets/sprites/misc/tile_marker.png");
		borderFrame.Render(pixel);
	}
	else if (m_action == DRAW_ENTITY)
	{
		if (m_renderSelection < 1.0) // If scrolled recently
		{
			m_renderSelection += elapsedTime;
			int i = 0;
			int iteratorNum = std::distance(m_selectedEntities->begin(), m_selectedEntityIterator);
			for (auto &entityMap : *m_selectedEntities)
			{ // Draw available tiles
				entityMap.second->RenderGraphics({pixel.x + 3 * TILESIZE * SCALE, pixel.y + (i++ - iteratorNum) * (TILESIZE * SCALE) * 2}, elapsedTime);
			}
		}
		m_selectedEntityIterator->second->RenderGraphics(m_mousePixel, elapsedTime);
	}

	m_dropdownMenu.Render();
}

void MapEditor::LoadScene()
{
	g_sfx.LoadMusic("chill-bass", "assets/sound/music/chill/chill-bass.wav");
	g_sfx.PlayMusic("chill-bass");

	ReadTilesFromFile("assets/maps/MapEditor.txt");
	m_player->SetPos({float(m_mapWidth) / 2, float(m_mapHeight) / 2});
}

void MapEditor::UnloadScene()
{
	// Entities and Tiles are automatically cleaned in base class.
	// You have to clean the sounds that you are leaving behind.
	g_sfx.FreeAll();
}
