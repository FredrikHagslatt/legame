#include "ECS.h"

/* Component */
int IComponent::nextId = 0;

/* Entity */
Entity::Entity(int id) : id(id) {}
int Entity::GetId() const { return id; }

/* System */
void System::AddEntityToSystem(Entity entity)
{
    entities.push_back(entity);
}
void System::RemoveEntityFromSystem(Entity entity)
{
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [&entity](Entity other)
                                  { return entity == other; }),
                   entities.end());
}
std::vector<Entity> System::GetSystemEntities() const
{
    return entities;
}
const Signature &System::GetComponentSignature() const
{
    return componentSignature;
}

/* Registry */

Entity Registry::CreateEntity()
{
    int entityId = numEntities++;
    Entity entity(entityId);
    entitiesToBeAdded.insert(entity);
    Logger::Log("Entity created with id = " + std::to_string(entityId));
    return entity;
}

void Registry::AddEntityToSystems(Entity entity)
{
    const int entityId = entity.GetId();
    const auto &entityComponentSignature = entityComponentSignatures[entityId];

    for (auto &system : systems)
    {
        const auto &systemComponentSignature = system.second->GetComponentSignature();
        if ((entityComponentSignature & systemComponentSignature) == systemComponentSignature)
        {
            system.second->AddEntityToSystem(entity);
        }
    }
}

void Registry::Update()
{
    // TODO: Add waiting entities
    // TODO: Kill waiting entities
}