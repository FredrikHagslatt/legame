#ifndef ENTITYEXPLORER_H
#define ENTITYEXPLORER_H

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_sdlrenderer.h>
#include <imgui/imgui_stdlib.h>
#include "entt/entt.hpp"
#include "AssetStore/AssetStore.h"

class EntityExplorer
{
private:
    std::shared_ptr<entt::registry> m_registry;
    std::shared_ptr<AssetStore> m_assetStore;
    bool showRegistry = true;

    std::vector<std::string> entityFilter;
    void ShowFilter();
    bool PassFilter(entt::entity entity);
    entt::entity selectedEntity;
    void ShowEntities();

    std::vector<std::string> availableComponents;
    std::size_t selectedAvailableComponentIndex = 0;
    std::vector<std::string> addedComponents;
    std::size_t selectedAddedComponentIndex = 0;

    // GUI
    void ShowComponents();
    void AvailableComponents();
    void AddComponentsButton();
    void AddedComponents();
    void DeleteComponentsButton();
    void ComponentAttributes();

    // Function
    void AddComponent(std::string componentName);
    void DeleteComponent(std::string componentName);
    std::vector<std::string> GetComponents(const entt::entity entity);

public:
    EntityExplorer(std::shared_ptr<entt::registry> registry,
                   std::shared_ptr<AssetStore> assetStore);
    void Render();
};

#endif