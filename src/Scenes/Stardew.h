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
#include "Components/KeyboardControlled.h"
#include "Components/ProjectileEmitter.h"
#include "Components/Health.h"
#include "Components/TextLabel.h"

#include "Systems/AnimationSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/KeyboardControlSystem.h"
#include "Systems/ProjectileEmitSystem.h"
#include "Systems/ProjectileLifecycleSystem.h"
#include "Systems/CameraMovementSystem.h"
#include "Systems/DamageSystem.h"
#include "Systems/CollisionSystem.h"

#include "Systems/RenderSystem.h"
#include "Systems/RenderHealthSystem.h"
#include "Systems/RenderTextSystem.h"
#include "Systems/RenderColliderSystem.h"

#include "SceneManager/Scene.h"
#include "AssetStore/AssetStore.h"

#include "Events/EventDispatcher.h"
#include "Events/KeyPressedEvent.h"

class Stardew : public Scene
{
protected:
	// Stardew
	SDL_Rect camera;
	void LoadLevel();
	void LoadMap(std::string spritesheet, std::string map);
	bool debugMode = false;

public:
	// Misc
	void ToggleDebugMode(const KeyPressedEvent &event);

	// Funcs for children
	virtual void UpdateScene(double elapsedTime) = 0;
	virtual void RenderScene(double elapsedTime) = 0;
	virtual void LoadScene() = 0;
	virtual void UnloadScene() = 0;

	// Scene
	void Update(double elapsedTime) override;
	void RenderGraphics(double elapsedTime) override;
	void Load() override;
	void Unload() override;
	Stardew(SDL_Renderer *renderer, std::shared_ptr<entt::registry> registry, std::shared_ptr<AssetStore> assetStore);
};

#endif