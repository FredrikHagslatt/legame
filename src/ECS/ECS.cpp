#include "ECS.h"

/* Component */
int IComponent::nextId = 0;

/* Entity */
int Entity::GetId() const { return id; }

/* System */
void System::AddEntityToSystem(Entity entity)
{
    entities.push_back(entity);
}
void System::RemoveEntityFromSystem(Entity entity)
{
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [&entity](Entity rhs)
                                  { return entity == rhs; }),
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
    entity.registry = this;
    entitiesToBeAdded.insert(entity);

    if (entityId >= static_cast<int>(entityComponentSignatures.size()))
    {
        entityComponentSignatures.resize(entityId + 1);
    }

    Logger::Info("Entity created with id = " + std::to_string(entityId));
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
    for (auto entity: entitiesToBeAdded)
    {
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    // TODO: Kill waiting entities
}