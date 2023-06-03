#ifndef XML_HANDLER_H
#define XML_HANDLER_H

#include <memory>
#include <iostream>
#include <string>
#include "entt/entt.hpp"
#include <SDL2/SDL.h>
#include "tinyxml2/tinyxml2.h"
#include "AssetStore/AssetStore.h"

#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Components/Velocity.h"
#include "Components/Sprite.h"
#include "Components/Animation.h"
#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"
#include "Components/Projectile.h"
#include "Components/ProjectileEmitter.h"
#include "Components/MenuNavigator.h"
#include "Components/Health.h"
#include "Components/TextLabel.h"
#include "Components/SceneSwitcher.h"

class XMLHandler
{
private:
    static bool FileExists(const std::string filename);

    static void SaveAnimation(tinyxml2::XMLElement *components, const Animation animatino);
    static void SaveBoxCollider(tinyxml2::XMLElement *components, const BoxCollider boxCollider);
    static void SaveCircleCollider(tinyxml2::XMLElement *components, const CircleCollider circleCollider);
    static void SaveHealth(tinyxml2::XMLElement *components, const Health health);
    static void SaveMenuNavigator(tinyxml2::XMLElement *components, const MenuNavigator menuNavigator);
    static void SaveProjectile(tinyxml2::XMLElement *components, const Projectile projectile);
    static void SaveProjectileEmitter(tinyxml2::XMLElement *components, const ProjectileEmitter projectileEmitter);
    static void SaveSceneSwitcher(tinyxml2::XMLElement *components, const SceneSwitcher sceneSwitcher);
    static void SaveSprite(tinyxml2::XMLElement *components, const Sprite sprite);
    static void SaveTextLabel(tinyxml2::XMLElement *components, const TextLabel textLabel);
    static void SaveTransform(tinyxml2::XMLElement *components, const Transform transform);
    static void SaveVelocity(tinyxml2::XMLElement *components, const Velocity velocity);

    static void SaveTags(tinyxml2::XMLElement *components, const std::shared_ptr<entt::registry> registry, const entt::entity entity);
    static void LoadTags(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);

    static void LoadAnimation(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);
    static void LoadBoxCollider(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);
    static void LoadCircleCollider(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);
    static void LoadHealth(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);
    static void LoadMenuNavigator(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);
    static void LoadProjectile(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);
    static void LoadProjectileEmitter(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);
    static void LoadSceneSwitcher(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);
    static void LoadSprite(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);
    static void LoadTextLabel(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);
    static void LoadTransform(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);
    static void LoadVelocity(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);

    static void LoadComponent(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component);
    static void SaveEntityToXML(const std::shared_ptr<entt::registry> registry, tinyxml2::XMLElement *component, const entt::entity entity);

    static void LoadAssets(tinyxml2::XMLElement *root, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore);
    static void LoadEntities(tinyxml2::XMLElement *root, std::shared_ptr<entt::registry> registry, std::shared_ptr<AssetStore> assetStore);

public:
    static std::pair<std::string, std::string> GetMapInfoFromXML(std::string filename);
    static void LoadFromXML(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore, std::string filename);
    static void SaveToXML(const std::shared_ptr<entt::registry> registry);
};
#endif