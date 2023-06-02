#include <algorithm>

#include "EntityExplorer.h"
#include "Logger/Logger.h"
#include "entt/entt.hpp"

#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Components/Velocity.h"
#include "Components/Sprite.h"
#include "Components/Animation.h"
#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"
#include "Components/Projectile.h"
#include "Components/ProjectileEmitter.h"
#include "Components/Health.h"
#include "Components/TextLabel.h"
#include "Components/SceneSwitcher.h"
#include "Components/MenuNavigator.h"

EntityExplorer::EntityExplorer(std::shared_ptr<entt::registry> registry,
                               std::shared_ptr<AssetStore> assetStore) : m_registry(registry), m_assetStore(assetStore)
{
    availableComponents =
        {"Animation",
         "BoxCollider",
         "CircleCollider",
         "Health",
         "Projectile",
         "ProjectileEmitter",
         "SceneSwitcher",
         "Sprite",
         "TextLabel",
         "Transform",
         "Velocity",

         "KeyboardControlled_Tag",
         "Enemy_Tag",
         "Obstacle_Tag",
         "Projectile_Tag",
         "StayOnMap_Tag",
         "Trigger_Tag",
         "Airborne_Tag",
         "Effect_Tag",
         "UI_Tag"};
}

void EntityExplorer::ShowFilter()
{
    static bool bAnimation = true;
    static bool bBoxCollider = true;
    static bool bCircleCollider = true;
    static bool bHealth = true;
    static bool bProjectile = true;
    static bool bProjectileEmitter = true;
    static bool bSceneSwitcher = true;
    static bool bSprite = true;
    static bool bTextLabel = true;
    static bool bTransform = true;
    static bool bVelocity = true;
    static bool bKeyboardControlled_Tag = true;
    static bool bEnemy_Tag = true;
    static bool bObstacle_Tag = true;
    static bool bProjectile_Tag = true;
    static bool bStayOnMap_Tag = true;
    static bool bTrigger_Tag = true;
    static bool bAirborne_Tag = true;
    static bool bEffect_Tag = true;
    static bool bUI_Tag = true;

    if (ImGui::CollapsingHeader("Filter"))
    {
        ImGui::BeginGroup();
        ImGui::Checkbox("Animation", &bAnimation);
        ImGui::Checkbox("BoxCollider", &bBoxCollider);
        ImGui::Checkbox("CircleCollider", &bCircleCollider);
        ImGui::Checkbox("Health", &bHealth);
        ImGui::Checkbox("Projectile", &bProjectile);
        ImGui::Checkbox("ProjectileEmitter", &bProjectileEmitter);
        ImGui::EndGroup();

        ImGui::SameLine();

        ImGui::BeginGroup();
        ImGui::Checkbox("SceneSwitcher", &bSceneSwitcher);
        ImGui::Checkbox("Sprite", &bSprite);
        ImGui::Checkbox("TextLabel", &bTextLabel);
        ImGui::Checkbox("Transform", &bTransform);
        ImGui::Checkbox("Velocity", &bVelocity);
        ImGui::EndGroup();

        ImGui::SameLine();

        ImGui::BeginGroup();
        ImGui::Checkbox("KeyboardControlled_Tag", &bKeyboardControlled_Tag);
        ImGui::Checkbox("Enemy_Tag", &bEnemy_Tag);
        ImGui::Checkbox("Obstacle_Tag", &bObstacle_Tag);
        ImGui::Checkbox("Projectile_Tag", &bProjectile_Tag);
        ImGui::Checkbox("StayOnMap_Tag", &bStayOnMap_Tag);
        ImGui::Checkbox("Trigger_Tag", &bTrigger_Tag);
        ImGui::Checkbox("Airborne_Tag", &bAirborne_Tag);
        ImGui::Checkbox("Effect_Tag", &bEffect_Tag);
        ImGui::Checkbox("UI_Tag", &bUI_Tag);
        ImGui::EndGroup();
    }

    entityFilter.clear();

    if (!bAnimation)
    {
        entityFilter.push_back("Animation");
    }
    if (!bBoxCollider)
    {
        entityFilter.push_back("BoxCollider");
    }
    if (!bCircleCollider)
    {
        entityFilter.push_back("CircleCollider");
    }
    if (!bHealth)
    {
        entityFilter.push_back("Health");
    }
    if (!bProjectile)
    {
        entityFilter.push_back("Projectile");
    }
    if (!bProjectileEmitter)
    {
        entityFilter.push_back("ProjectileEmitter");
    }
    if (!bSceneSwitcher)
    {
        entityFilter.push_back("SceneSwitcher");
    }
    if (!bSprite)
    {
        entityFilter.push_back("Sprite");
    }
    if (!bTextLabel)
    {
        entityFilter.push_back("bTextLabel");
    }
    if (!bTransform)
    {
        entityFilter.push_back("bTransform");
    }
    if (!bVelocity)
    {
        entityFilter.push_back("bVelocity");
    }
    if (!bKeyboardControlled_Tag)
    {
        entityFilter.push_back("bKeyboardControlled_Tag");
    }
    if (!bEnemy_Tag)
    {
        entityFilter.push_back("bEnemy_Tag");
    }
    if (!bObstacle_Tag)
    {
        entityFilter.push_back("bObstacle_Tag");
    }
    if (!bProjectile_Tag)
    {
        entityFilter.push_back("bProjectile_Tag");
    }
    if (!bStayOnMap_Tag)
    {
        entityFilter.push_back("bStayOnMap_Tag");
    }
    if (!bTrigger_Tag)
    {
        entityFilter.push_back("bTrigger_Tag");
    }
    if (!bAirborne_Tag)
    {
        entityFilter.push_back("bAirborne_Tag");
    }
    if (!bEffect_Tag)
    {
        entityFilter.push_back("bEffect_Tag");
    }
    if (!bUI_Tag)
    {
        entityFilter.push_back("bUI_Tag");
    }
}

bool EntityExplorer::PassFilter(entt::entity entity)
{
    bool passedFilter = true;

    for (auto componentName : entityFilter)
    {
        if (componentName == "Animation")
        {
            if (m_registry->any_of<Animation>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "BoxCollider")
        {
            if (m_registry->any_of<BoxCollider>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "CircleCollider")
        {
            if (m_registry->any_of<CircleCollider>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "Health")
        {
            if (m_registry->any_of<Health>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "MenuNavigator")
        {
            if (m_registry->any_of<MenuNavigator>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "Projectile")
        {
            if (m_registry->any_of<Projectile>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "ProjectileEmitter")
        {
            if (m_registry->any_of<ProjectileEmitter>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "SceneSwitcher")
        {
            if (m_registry->any_of<SceneSwitcher>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "Sprite")
        {
            if (m_registry->any_of<Sprite>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "TextLabel")
        {
            if (m_registry->any_of<TextLabel>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "Transform")
        {
            if (m_registry->any_of<Transform>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "Velocity")
        {
            if (m_registry->any_of<Velocity>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "Velocity")
        {
            if (m_registry->any_of<Velocity>(entity))
            {
                passedFilter = false;
            }
        }

        // Tags
        else if (componentName == "KeyboardControlled_Tag")
        {
            if (m_registry->any_of<KeyboardControlled_Tag>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "Enemy_Tag")
        {
            if (m_registry->any_of<Enemy_Tag>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "Obstacle_Tag")
        {
            if (m_registry->any_of<Obstacle_Tag>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "Projectile_Tag")
        {
            if (m_registry->any_of<Projectile_Tag>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "StayOnMap_Tag")
        {
            if (m_registry->any_of<StayOnMap_Tag>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "Trigger_Tag")
        {
            if (m_registry->any_of<Trigger_Tag>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "Airborne_Tag")
        {
            if (m_registry->any_of<Airborne_Tag>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "Effect_Tag")
        {
            if (m_registry->any_of<Effect_Tag>(entity))
            {
                passedFilter = false;
            }
        }
        else if (componentName == "UI_Tag")
        {
            if (m_registry->any_of<UI_Tag>(entity))
            {
                passedFilter = false;
            }
        }
    }
    return passedFilter;
}

void EntityExplorer::ShowEntities()
{
    int count = 0;
    static int selectedEntityIndex = 0;
    std::vector<std::string> entities;
    m_registry->each([&count, &entities, this](entt::entity entity)
                     {
                         if (PassFilter(entity))
                         {
                            std::string entityNum = "Entity " + std::to_string(count);
                            entities.push_back(entityNum);
                            if (count == selectedEntityIndex)
                            {
                                this->selectedEntity = entity;
                            }

                            count++;
                         } });

    ImGui::Text("Entities");

    if (entities.empty())
    {
        entities.push_back("No entities.");
    }

    if (ImGui::BeginListBox("##Entities"))
    {
        for (int n = 0; n < entities.size(); n++)
        {
            const bool isSelected = (selectedEntityIndex == n);
            if (ImGui::Selectable(entities.at(n).c_str(), isSelected))
                selectedEntityIndex = n;

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }
}

void EntityExplorer::AvailableComponents()
{
    ImGui::Text("Available Components");
    if (ImGui::BeginListBox("##Available Components"))
    {
        selectedAvailableComponentIndex = std::min(selectedAvailableComponentIndex, availableComponents.size() - 1);
        for (int n = 0; n < availableComponents.size(); n++)
        {
            const bool isSelected = (selectedAvailableComponentIndex == n);
            if (ImGui::Selectable(availableComponents.at(n).c_str(), isSelected))
                selectedAvailableComponentIndex = n;

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }
}

void EntityExplorer::AddedComponents()
{
    addedComponents = GetComponents(selectedEntity);

    ImGui::Text("Added Components");
    if (ImGui::BeginListBox("##Added Components"))
    {
        selectedAddedComponentIndex = std::min(selectedAddedComponentIndex, addedComponents.size() - 1);
        for (int n = 0; n < addedComponents.size(); n++)
        {
            const bool isSelected = (selectedAddedComponentIndex == n);
            if (ImGui::Selectable(addedComponents.at(n).c_str(), isSelected))
                selectedAddedComponentIndex = n;

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }
}

void EntityExplorer::ComponentAttributes()
{

    std::string componentName = addedComponents.at(selectedAddedComponentIndex);
    std::string headerString = componentName + " Attributes";
    ImGui::Text(headerString.c_str());

    if (componentName == "Animation")
    {
        auto &animation = m_registry->get<Animation>(selectedEntity);
        ImGui::InputInt("numFrames", &animation.numFrames);
        ImGui::InputInt("frameRateSpeed", &animation.frameRateSpeed);
        ImGui::Checkbox("isLoop", &animation.isLoop);
        ImGui::Checkbox("hasDirections", &animation.hasDirections);
    }
    else if (componentName == "BoxCollider")
    {
        auto &boxCollider = m_registry->get<BoxCollider>(selectedEntity);
        ImGui::InputInt("width", &boxCollider.width);
        ImGui::InputInt("height", &boxCollider.height);
        ImGui::InputFloat("offset.x", &boxCollider.offset.x);
        ImGui::InputFloat("offset.y", &boxCollider.offset.y);
    }
    else if (componentName == "CircleCollider")
    {
        auto &circleCollider = m_registry->get<CircleCollider>(selectedEntity);
        ImGui::InputInt("radius", &circleCollider.radius);
        ImGui::InputFloat("offset.x", &circleCollider.offset.x);
        ImGui::InputFloat("offset.y", &circleCollider.offset.y);
    }
    else if (componentName == "Health")
    {
        auto &health = m_registry->get<Health>(selectedEntity);
        ImGui::InputInt("hitPoints", &health.hitPoints);
    }
    else if (componentName == "MenuNavigator")
    {
        auto &menuNavigator = m_registry->get<MenuNavigator>(selectedEntity);
        ImGui::InputInt("numRows", &menuNavigator.numRows);
        ImGui::InputInt("rowDistance", &menuNavigator.rowDistance);
        ImGui::InputInt("atRow", &menuNavigator.atRow);
    }
    else if (componentName == "Projectile")
    {
        auto &projectile = m_registry->get<Projectile>(selectedEntity);
        ImGui::Checkbox("isFriendly", &projectile.isFriendly);
        ImGui::InputInt("numRows", &projectile.hitPercentDamage);
        ImGui::InputInt("numRows", &projectile.duration);
    }
    else if (componentName == "ProjectileEmitter")
    {
        auto &projectileEmitter = m_registry->get<ProjectileEmitter>(selectedEntity);
        ImGui::InputDouble("speed", &projectileEmitter.speed);
        ImGui::InputFloat("direction.x", &projectileEmitter.direction.x);
        ImGui::InputFloat("direction.y", &projectileEmitter.direction.y);
        ImGui::InputInt("repeatFrequency", &projectileEmitter.repeatFrequency);
        ImGui::InputInt("duration", &projectileEmitter.duration);
        ImGui::InputInt("hitPercentDamage", &projectileEmitter.hitPercentDamage);
        ImGui::Checkbox("isFriendly", &projectileEmitter.isFriendly);
        ImGui::Checkbox("inheritDirection", &projectileEmitter.inheritDirection);
    }
    else if (componentName == "SceneSwitcher")
    {
        auto &sceneSwitcher = m_registry->get<SceneSwitcher>(selectedEntity);

        ImGui::InputText("sceneManagerId", &sceneSwitcher.sceneManagerId);
        ImGui::InputText("sceneName", &sceneSwitcher.sceneName);
    }
    else if (componentName == "Sprite")
    {
        auto &sprite = m_registry->get<Sprite>(selectedEntity);
        ImGui::InputText("assetId", &sprite.assetId);
        ImGui::InputInt("width", &sprite.width);
        ImGui::InputInt("height", &sprite.height);
        ImGui::InputInt("pivotPoint", &sprite.pivotPoint);
        ImGui::Checkbox("fixedPosition", &sprite.fixedPosition);
        ImGui::InputInt("scrRect.x", &sprite.srcRect.x);
        ImGui::InputInt("srcRect.y", &sprite.srcRect.y);
    }
    else if (componentName == "TextLabel")
    {
        auto &textLabel = m_registry->get<TextLabel>(selectedEntity);
        ImGui::InputFloat("position.x", &textLabel.position.x);
        ImGui::InputFloat("position.y", &textLabel.position.y);
        ImGui::InputText("text", &textLabel.text);
        ImGui::InputText("assetId", &textLabel.assetId);

        float color[3] = {(float)textLabel.color.r / 255.0f, (float)textLabel.color.g / 255.0f, (float)textLabel.color.b / 255.0f};
        ImGui::ColorEdit3("color", color);
        textLabel.color = {(Uint8)(color[0] * 255.0f), (Uint8)(color[1] * 255.0f), (Uint8)(color[2] * 255.0f)};

        ImGui::Checkbox("isFixed", &textLabel.isFixed);
    }
    else if (componentName == "Transform")
    {
        auto &transform = m_registry->get<Transform>(selectedEntity);
        ImGui::InputFloat("position.x", &transform.position.x);
        ImGui::InputFloat("position.y", &transform.position.y);
        ImGui::InputFloat("scale.x", &transform.scale.x);
        ImGui::InputFloat("scale.y", &transform.scale.y);
        ImGui::InputDouble("rotation", &transform.rotation);
    }
    else if (componentName == "Velocity")
    {
        auto &velocity = m_registry->get<Velocity>(selectedEntity);
        ImGui::InputDouble("speed", &velocity.speed, 10, 100);

        int dirX = static_cast<int>(velocity.direction.x);
        ImGui::InputInt("direction.x", &dirX, 1, 1);
        dirX = std::min(1, dirX);
        dirX = std::max(-1, dirX);
        velocity.direction.x = dirX;

        int dirY = static_cast<int>(velocity.direction.y);
        ImGui::InputInt("direction.y", &dirY, 1, 1);
        dirY = std::min(1, dirY);
        dirY = std::max(-1, dirY);
        velocity.direction.y = dirY;

        int lastX = static_cast<int>(velocity.lastNonZeroDirection.x);
        ImGui::InputInt("lastNonZeroDirection.x", &lastX, 1, 1);
        lastX = std::min(1, lastX);
        lastX = std::max(-1, lastX);
        velocity.lastNonZeroDirection.x = lastX;

        int lastY = static_cast<int>(velocity.lastNonZeroDirection.y);
        ImGui::InputInt("lastNonZeroDirection.y", &lastY, 1, 1);
        lastY = std::min(1, lastY);
        lastY = std::max(-1, lastY);
        velocity.lastNonZeroDirection.y = lastY;
    }
}

void EntityExplorer::AddComponentsButton()
{
    if (ImGui::Button("Add Component"))
    {
        std::string componentName = availableComponents.at(selectedAvailableComponentIndex);
        AddComponent(componentName);
    }
}

void EntityExplorer::DeleteComponentsButton()
{
    if (ImGui::Button("Delete Component"))
    {
        if (addedComponents.empty())
        {
            Logger::Info("No components to delete, you simpleton");
        }
        else
        {
            std::string componentName = addedComponents.at(selectedAddedComponentIndex);
            DeleteComponent(componentName);
        }
    }
}

void EntityExplorer::ShowComponents()
{

    ImGui::BeginGroup();
    AvailableComponents();
    AddComponentsButton();
    ImGui::EndGroup();

    ImGui::SameLine();

    ImGui::BeginGroup();
    AddedComponents();
    DeleteComponentsButton();
    ImGui::EndGroup();

    ImGui::SameLine();

    ImGui::BeginGroup();
    ComponentAttributes();
    ImGui::EndGroup();
}

void EntityExplorer::Render()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
    if (ImGui::Begin("EntityExplorer", NULL, window_flags))
    {
        ShowFilter();
        ShowEntities();
        ShowComponents();
    }

    ImGui::End();
}

std::vector<std::string> EntityExplorer::GetComponents(const entt::entity entity)
{

    std::vector<std::string> components = {};

    if (m_registry->all_of<Animation>(entity))
    {
        components.push_back("Animation");
    }
    if (m_registry->all_of<BoxCollider>(entity))
    {
        components.push_back("BoxCollider");
    }
    if (m_registry->all_of<CircleCollider>(entity))
    {
        components.push_back("CircleCollider");
    }
    if (m_registry->all_of<Health>(entity))
    {
        components.push_back("Health");
    }
    if (m_registry->all_of<MenuNavigator>(entity))
    {
        components.push_back("MenuNavigator");
    }
    if (m_registry->all_of<Projectile>(entity))
    {
        components.push_back("Projectile");
    }
    if (m_registry->all_of<ProjectileEmitter>(entity))
    {
        components.push_back("ProjectileEmitter");
    }
    if (m_registry->all_of<SceneSwitcher>(entity))
    {
        components.push_back("SceneSwitcher");
    }
    if (m_registry->all_of<Sprite>(entity))
    {
        components.push_back("Sprite");
    }
    if (m_registry->all_of<TextLabel>(entity))
    {
        components.push_back("TextLabel");
    }
    if (m_registry->all_of<Transform>(entity))
    {
        components.push_back("Transform");
    }
    if (m_registry->all_of<Velocity>(entity))
    {
        components.push_back("Velocity");
    }
    // Tags
    if (m_registry->all_of<KeyboardControlled_Tag>(entity))
    {
        components.push_back("KeyboardControlled_Tag");
    }
    if (m_registry->all_of<Enemy_Tag>(entity))
    {
        components.push_back("Enemy_Tag");
    }
    if (m_registry->all_of<Obstacle_Tag>(entity))
    {
        components.push_back("Obstacle_Tag");
    }
    if (m_registry->all_of<Projectile_Tag>(entity))
    {
        components.push_back("Projectile_Tag");
    }
    if (m_registry->all_of<StayOnMap_Tag>(entity))
    {
        components.push_back("StayOnMap_Tag");
    }
    if (m_registry->all_of<Trigger_Tag>(entity))
    {
        components.push_back("Trigger_Tag");
    }
    if (m_registry->all_of<Airborne_Tag>(entity))
    {
        components.push_back("Airborne_Tag");
    }
    if (m_registry->all_of<Effect_Tag>(entity))
    {
        components.push_back("Effect_Tag");
    }
    if (m_registry->all_of<UI_Tag>(entity))
    {
        components.push_back("UI_Tag");
    }
    return components;
}

void EntityExplorer::AddComponent(std::string componentName)
{
    Logger::Info("Adding Component: " + componentName);

    if (componentName == "Animation")
    {
        if (!m_registry->any_of<Animation>(selectedEntity))
        {
            m_registry->emplace<Animation>(selectedEntity);
        }
    }
    else if (componentName == "BoxCollider")
    {
        if (!m_registry->any_of<BoxCollider>(selectedEntity))
        {
            m_registry->emplace<BoxCollider>(selectedEntity);
        }
    }
    else if (componentName == "CircleCollider")
    {
        if (!m_registry->any_of<CircleCollider>(selectedEntity))
        {
            m_registry->emplace<CircleCollider>(selectedEntity);
        }
    }
    else if (componentName == "Health")
    {
        if (!m_registry->any_of<Health>(selectedEntity))
        {
            m_registry->emplace<Health>(selectedEntity);
        }
    }
    else if (componentName == "MenuNavigator")
    {
        if (!m_registry->any_of<MenuNavigator>(selectedEntity))
        {
            m_registry->emplace<MenuNavigator>(selectedEntity);
        }
    }
    else if (componentName == "Projectile")
    {
        if (!m_registry->any_of<Projectile>(selectedEntity))
        {
            m_registry->emplace<Projectile>(selectedEntity);
        }
    }
    else if (componentName == "ProjectileEmitter")
    {
        if (!m_registry->any_of<ProjectileEmitter>(selectedEntity))
        {
            m_registry->emplace<ProjectileEmitter>(selectedEntity);
        }
    }
    else if (componentName == "SceneSwitcher")
    {
        if (!m_registry->any_of<SceneSwitcher>(selectedEntity))
        {
            m_registry->emplace<SceneSwitcher>(selectedEntity);
        }
    }
    else if (componentName == "Sprite")
    {
        if (!m_registry->any_of<Sprite>(selectedEntity))
        {
            m_registry->emplace<Sprite>(selectedEntity);
        }
    }
    else if (componentName == "TextLabel")
    {
        if (!m_registry->any_of<TextLabel>(selectedEntity))
        {
            m_registry->emplace<TextLabel>(selectedEntity);
        }
    }
    else if (componentName == "Transform")
    {
        if (!m_registry->any_of<Transform>(selectedEntity))
        {
            m_registry->emplace<Transform>(selectedEntity);
        }
    }
    else if (componentName == "Velocity")
    {
        if (!m_registry->any_of<Velocity>(selectedEntity))
        {
            m_registry->emplace<Velocity>(selectedEntity);
        }
    }
    else if (componentName == "Velocity")
    {
        if (!m_registry->any_of<Velocity>(selectedEntity))
        {
            m_registry->emplace<Velocity>(selectedEntity);
        }
    }

    // Tags
    else if (componentName == "KeyboardControlled_Tag")
    {
        if (!m_registry->any_of<KeyboardControlled_Tag>(selectedEntity))
        {
            m_registry->emplace<KeyboardControlled_Tag>(selectedEntity);
        }
    }
    else if (componentName == "Enemy_Tag")
    {
        if (!m_registry->any_of<Enemy_Tag>(selectedEntity))
        {
            m_registry->emplace<Enemy_Tag>(selectedEntity);
        }
    }
    else if (componentName == "Obstacle_Tag")
    {
        if (!m_registry->any_of<Obstacle_Tag>(selectedEntity))
        {
            m_registry->emplace<Obstacle_Tag>(selectedEntity);
        }
    }
    else if (componentName == "Projectile_Tag")
    {
        if (!m_registry->any_of<Projectile_Tag>(selectedEntity))
        {
            m_registry->emplace<Projectile_Tag>(selectedEntity);
        }
    }
    else if (componentName == "StayOnMap_Tag")
    {
        if (!m_registry->any_of<StayOnMap_Tag>(selectedEntity))
        {
            m_registry->emplace<StayOnMap_Tag>(selectedEntity);
        }
    }
    else if (componentName == "Trigger_Tag")
    {
        if (!m_registry->any_of<Trigger_Tag>(selectedEntity))
        {
            m_registry->emplace<Trigger_Tag>(selectedEntity);
        }
    }
    else if (componentName == "Airborne_Tag")
    {
        if (!m_registry->any_of<Airborne_Tag>(selectedEntity))
        {
            m_registry->emplace<Airborne_Tag>(selectedEntity);
        }
    }
    else if (componentName == "Effect_Tag")
    {
        if (!m_registry->any_of<Effect_Tag>(selectedEntity))
        {
            m_registry->emplace<Effect_Tag>(selectedEntity);
        }
    }
    else if (componentName == "UI_Tag")
    {
        if (!m_registry->any_of<UI_Tag>(selectedEntity))
        {
            m_registry->emplace<UI_Tag>(selectedEntity);
        }
    }
}

void EntityExplorer::DeleteComponent(std::string componentName)
{
    Logger::Info("Deleting Component: " + componentName);

    if (componentName == "Animation")
    {
        m_registry->remove<Animation>(selectedEntity);
    }
    else if (componentName == "BoxCollider")
    {
        m_registry->remove<BoxCollider>(selectedEntity);
    }
    else if (componentName == "CircleCollider")
    {
        m_registry->remove<CircleCollider>(selectedEntity);
    }
    else if (componentName == "Health")
    {
        m_registry->remove<Health>(selectedEntity);
    }
    else if (componentName == "MenuNavigator")
    {
        m_registry->remove<MenuNavigator>(selectedEntity);
    }
    else if (componentName == "Projectile")
    {
        m_registry->remove<Projectile>(selectedEntity);
    }
    else if (componentName == "ProjectileEmitter")
    {
        m_registry->remove<ProjectileEmitter>(selectedEntity);
    }
    else if (componentName == "SceneSwitcher")
    {
        m_registry->remove<SceneSwitcher>(selectedEntity);
    }
    else if (componentName == "Sprite")
    {
        m_registry->remove<Sprite>(selectedEntity);
    }
    else if (componentName == "TextLabel")
    {
        m_registry->remove<TextLabel>(selectedEntity);
    }
    else if (componentName == "Transform")
    {
        m_registry->remove<Transform>(selectedEntity);
    }
    else if (componentName == "Velocity")
    {
        m_registry->remove<Velocity>(selectedEntity);
    }

    // Tags
    else if (componentName == "KeyboardControlled_Tag")
    {
        m_registry->remove<KeyboardControlled_Tag>(selectedEntity);
    }

    else if (componentName == "Enemy_Tag")
    {
        m_registry->remove<Enemy_Tag>(selectedEntity);
    }

    else if (componentName == "Obstacle_Tag")
    {
        m_registry->remove<Obstacle_Tag>(selectedEntity);
    }
    else if (componentName == "Projectile_Tag")
    {
        m_registry->remove<Projectile_Tag>(selectedEntity);
    }
    else if (componentName == "StayOnMap_Tag")
    {
        m_registry->remove<StayOnMap_Tag>(selectedEntity);
    }
    else if (componentName == "Trigger_Tag")
    {
        m_registry->remove<Trigger_Tag>(selectedEntity);
    }
    else if (componentName == "Airborne_Tag")
    {
        m_registry->remove<Airborne_Tag>(selectedEntity);
    }
    else if (componentName == "Effect_Tag")
    {
        m_registry->remove<Effect_Tag>(selectedEntity);
    }
    else if (componentName == "UI_Tag")
    {
        m_registry->remove<UI_Tag>(selectedEntity);
    }
}
