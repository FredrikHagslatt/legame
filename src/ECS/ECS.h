#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <algorithm>
#include <typeindex>
#include <unordered_map>

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
    int GetId() const;
    bool operator==(const Entity &other) { return id == other.id; };
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
    virtual ~IPool(){}
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
        return static_cast<TComponent&>(data[index]);
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

    std::vector<IPool*> componentPools;
    std::vector<Signature> entityComponentSignatures;
    std::unordered_map<std::type_index, System*> systems;

public:
    Registry() = default;

    //Entity CreateEntity();
    //void KillEntity(Entity entity);
    //void AddSystem();
    //void AddComponent();
    //void RemoveComponent();

    //AddSystem();
    //RemoveSystem();
    //HasSystem();
    //GetSystem();

};

template <typename TComponent>
void System::RequireComponent()
{
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
};

#endif