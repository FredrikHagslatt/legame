#ifndef XML_HANDLER_H
#define XML_HANDLER_H

#include <memory>
#include <iostream>
#include <string>
#include "entt/entt.hpp"
#include "tinyxml2/tinyxml2.h"

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
    static void SaveAnimation(tinyxml2::XMLElement *components, Animation animatino);
    static void SaveBoxCollider(tinyxml2::XMLElement *components, BoxCollider boxCollider);
    static void SaveCircleCollider(tinyxml2::XMLElement *components, CircleCollider circleCollider);
    static void SaveHealth(tinyxml2::XMLElement *components, Health health);
    static void SaveMenuNavigator(tinyxml2::XMLElement *components, MenuNavigator menuNavigator);
    static void SaveProjectile(tinyxml2::XMLElement *components, Projectile projectile);
    static void SaveProjectileEmitter(tinyxml2::XMLElement *components, ProjectileEmitter projectileEmitter);
    static void SaveSceneSwitcher(tinyxml2::XMLElement *components, SceneSwitcher sceneSwitcher);
    static void SaveSprite(tinyxml2::XMLElement *components, Sprite sprite);
    static void SaveTextLabel(tinyxml2::XMLElement *components, TextLabel textLabel);
    static void SaveTransform(tinyxml2::XMLElement *components, Transform transform);
    static void SaveVelocity(tinyxml2::XMLElement *components, Velocity velocity);
    static void SaveTags(tinyxml2::XMLElement *components, std::shared_ptr<entt::registry> registry, entt::entity entity);
    static void AddTags(tinyxml2::XMLElement *component);
    static void AddComponent(tinyxml2::XMLElement *component);
    static void SaveEntityToXML(std::shared_ptr<entt::registry> registry, tinyxml2::XMLElement *component, entt::entity entity);

public:
    static void ReadFromXML();
    static void SaveToXML(std::shared_ptr<entt::registry> registry);
};
#endif