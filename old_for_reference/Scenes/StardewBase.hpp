#ifndef STARDEW_BASE_H
#define STARDEW_BASE_H

#include <math.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "entities/Player.hpp"
#include "entities/Entity.hpp"
#include "Constants.hpp"
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include "util/PixelPos.hpp"
#include "util/Collisions.hpp"
#include "entities/PredefinedEntities.hpp"

class StardewBase : public Scene
{

protected:
	Pixel PosToPixel(Pos pos);
	Pos PixelToPos(Pixel pixel);
	virtual void HandleKeyEvents();

	class Tile
	{
		Texture *m_texture;
		std::string m_sprite;
		int m_stateOfMatter; // matter property, 0 gothroughable, 1 solid.

		RectangularHitbox m_rectangularHitbox = RectangularHitbox({16, 16});
		NoHitbox m_noHitbox = NoHitbox();
		Hitbox *m_hitbox;

	public:
		Tile(std::string sprite, int stateOfMatter = 0);
		std::string GetSpritePath() { return m_sprite; }
		int GetStateOfMatter() { return m_stateOfMatter; }
		Hitbox *GetHitbox() { return m_hitbox; }

		void Render(Pixel pixel)
		{
			pixel.x += 8 * SCALE;
			pixel.y += 8 * SCALE;
			g_gfx.Render(*m_texture, pixel);
		}
	};

	struct
	{
		float x;
		float y;
		int xMin;
		int xMax;
		int yMin;
		int yMax;
	} m_camera;

	Player *m_player;
	std::list<Entity*> m_entities;
	std::list<Entity*> m_entitiesToCollisionCheck; //Moving objects that will collision check vs all objects.

	int m_mapWidth;
	int m_mapHeight;
	std::vector<Tile *> m_tiles;
	std::vector<std::vector<Tile *>> m_map;
	void ReadTilesFromFile(std::string FileName);

	void PrintFPS(double elapsedTime);
	double m_fpsTimer = 1.0;
	int m_frameCounter = 0;
	bool m_renderHitboxes = false; //Set true to debug hitboxes //Potential FPS KILLER!
	bool m_pauseEntities = false; //For mapeditor, or whenever you might need it.

public:
	// Funcs for children
	virtual void UpdateScene(double elapsedTime) = 0;
	virtual void RenderScene(double elapsedTime) = 0;
	virtual void LoadScene() = 0;
	virtual void UnloadScene() = 0;

	// Scene
	bool Update(double elapsedTime) override;
	void RenderGraphics(double elapsedTime) override;
	void Load() override;
	void Unload() override;
	StardewBase(SceneManager &sceneManager, Player *player);
};
#endif // STARDEW_BASE_H
