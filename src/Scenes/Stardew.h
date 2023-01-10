#ifndef STARDEW_H
#define STARDEW_H

#include <list>
#include <string>

#include "entt/entt.hpp"

#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Components/Velocity.h"
#include "Components/Sprite.h"
#include "Components/Animation.h"
#include "Components/BoxCollider.h"
#include "Components/ProjectileEmitter.h"
#include "Components/Health.h"
#include "Components/TextLabel.h"
#include "Components/SceneSwitcher.h"

#include "Systems/AnimationSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/KeyboardControlSystem.h"
#include "Systems/ProjectileEmitSystem.h"
#include "Systems/ProjectileLifecycleSystem.h"
#include "Systems/CameraMovementSystem.h"
#include "Systems/DamageSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/TriggerSystem.h"

#include "Systems/RenderTileMapSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/RenderHealthSystem.h"
#include "Systems/RenderTextSystem.h"
#include "Systems/RenderColliderSystem.h"

#include "SceneManager/Scene.h"
#include "AssetStore/AssetStore.h"

#include "Events/EventDispatcher.h"
#include "Events/KeyPressedEvent.h"

#include "XMLHandler/XMLHandler.h"

class Stardew : public Scene
{
protected:
	// Stardew
	int m_mapWidth = 0;
	int m_mapHeight = 0;
	SDL_Rect m_camera;
	std::vector<std::vector<Sprite>> m_tileMap;
	void LoadLevel();
	void LoadMap(std::string spritesheet, std::string map);

public:
	// Funcs for children
	virtual void UpdateScene(const double elapsedTime) = 0;
	virtual void RenderScene(const double elapsedTime) = 0;
	virtual void LoadScene() = 0;
	virtual void UnloadScene() = 0;

	// Scene
	void Update(const double elapsedTime) override;
	void RenderGraphics(const double elapsedTime) override;
	void Load() override;
	void Unload() override;
	Stardew(SDL_Renderer *renderer, std::shared_ptr<entt::registry> registry, std::shared_ptr<AssetStore> assetStore);
};

#endif