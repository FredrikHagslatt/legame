#ifndef ECS_H
#define ECS_H

#include "Logger/Logger.h"
#include <bitset>
#include <vector>
#include <algorithm>
#include <typeindex>
#include <memory>
#include <unordered_map>
#include <set>

const unsigned int MAX_COMPONENTS = 32;

/* Keeps track of which entities a system is interested in */
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent
{
protected:
    static int nextId;
};

/* Used to assign unique id to a component type */
template <typename TComponent>
class Component : public IComponent
{
public:
    static int GetId()
    {
        static auto id = nextId++;
        return id;
    }
};

class Entity
{
private:
    int id;

public:
    Entity(int id);
    Entity(const Entity &entity) = default;
    int GetId() const;

    Entity &operator=(const Entity &rhs) = default;
    bool operator==(const Entity &rhs) const { return id == rhs.id; };
    bool operator!=(const Entity &rhs) const { return id != rhs.id; };
    bool operator<(const Entity &rhs) const { return id < rhs.id; };
    bool operator>(const Entity &rhs) const { return id > rhs.id; };
};

class System
{
private:
    Signature componentSignature;
    std::vector<Entity> entities;

public:
    System() = default;
    virtual ~System() = default;
    void AddEntityToSystem(Entity entity);
    void RemoveEntityFromSystem(Entity entity);
    std::vector<Entity> GetSystemEntities() const;
    const Signature &GetComponentSignature() const;

    template <typename T>
    void RequireComponent();
};

class IPool
{
public:
    virtual ~IPool() {}
};

template <typename TComponent>
class Pool : IPool
{
private:
    std::vector<TComponent> data;

public:
    Pool(int size = 100)
    {
        data.Resize(size);
    }
    virtual ~Pool() = default;

    bool IsEmpty() const
    {
        return data.empty();
    }

    int getSize() const
    {
        return data.size();
    }

    void Resize(int n)
    {
        data.resize(n);
    }

    void Clear()
    {
        data.clear();
    }

    void Add(TComponent object)
    {
        data.push_back(object);
    }

    void Set(int index, TComponent object)
    {
        data[index] = object;
    }

    TComponent &Get(int index)
    {
        return static_cast<TComponent &>(data[index]);
    }

    TComponent &operator[](unsigned int index)
    {
        return data[index];
    }
};

/* Manages the created and destruction of entities, add systems and components */
class Registry
{
private:
    int numEntities = 0;
    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeKilled;

    std::vector<std::shared_ptr<IPool>> componentPools;
    std::vector<Signature> entityComponentSignatures;
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

public:
    /* Registry core */
    Registry() { Logger::Log("Registry Created"); };
    ~Registry() { Logger::Log("Registry Destroyed"); };

    void Update();

    /* Entity management */
    Entity CreateEntity();

    /* Component management */
    template <typename TComponent, typename... TArgs>
    void AddComponent(Entity entity, TArgs &&...args);

    template <typename TComponent>
    void RemoveComponent(Entity entity);

    template <typename TComponent>
    bool HasComponent(Entity entity) const;

    //    template <typename TComponent>
    //    TComponent &GetComponent(Entity entity);

    /* System Management */
    template <typename TSystem, typename... TArgs>
    void AddSystem(TArgs &&...args);
    template <typename TSystem>
    void RemoveSystem();
    template <typename TSystem>
    bool HasSystem() const;
    template <typename TSystem>
    TSystem &GetSystem() const;

    void AddEntityToSystems(Entity entity);
};

template <typename TComponent>
void System::RequireComponent()
{
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
};

template <typename TSystem, typename... TArgs>
void Registry::AddSystem(TArgs &&...args)
{
    std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Registry::RemoveSystem()
{
    TSystem system = systems.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
}

template <typename TSystem>
bool Registry::HasSystem() const
{
    return (systems.find(std::type_index(typeid(TSystem))) != systems.end());
}

template <typename TSystem>
TSystem &Registry::GetSystem() const
{
    auto system = systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(system->second));
}

template <typename TComponent, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs &&...args)
{
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    if (componentId >= static_cast<int>(componentPools.size()))
    {
        componentPools.resize(componentId + 1, nullptr);
    }

    if (!componentPools[componentId])
    {
        std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
        componentPools[componentId] = newComponentPool;
    }

    std::shared_ptr<Pool<TComponent>> componentPool =
        std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);

    if (entityId >= componentPool->GetSize())
    {
        componentPool->Resize(numEntities);
    }

    // Forward template arguments to the component constructor
    TComponent newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);
    entityComponentSignatures[entityId].set(componentId);
    Logger::Log(
        "Component id = " + std::to_string(componentId) + " was added to entity id = " + std::to_string(entityId) + ".");
}

template <typename TComponent>
void Registry::RemoveComponent(Entity entity)
{
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();
    entityComponentSignatures[entityId].reset(componentId);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const
{
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();
    return entityComponentSignatures[entityId].test(componentId);
}

/*
template <typename TComponent>
TComponent &Registry::GetComponent(Entity entity)
{
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();
    Pool<TComponent> *componentPool = Pool<TComponent>(componentPools[componentId]);
    return componentPool[entityId];
}
*/

#endif