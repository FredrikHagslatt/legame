#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "entt/entt.hpp"
#include "EventBus/EventBus.h"
#include "Events/CollisionEvent.h"
#include "Components/Transform.h"
#include "Components/BoxCollider.h"

/*

class CollisionSystem : public System
{
public:
    CollisionSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<BoxColliderComponent>();
    }

    void Update(std::unique_ptr<EventBus> &eventBus)
    {
        auto entities = GetSystemEntities();

        // Fancy nested loop to not check same pair of entities twice.
        for (auto i = entities.begin(); i != entities.end(); i++)
        {
            Entity a = *i;
            for (auto j = i; j != entities.end(); j++)
            {
                Entity b = *j;

                if (a == b)
                {
                    continue;
                }

                auto aTransform = a.GetComponent<TransformComponent>();
                auto aCollider = a.GetComponent<BoxColliderComponent>();

                auto bTransform = b.GetComponent<TransformComponent>();
                auto bCollider = b.GetComponent<BoxColliderComponent>();

                bool collisionHappened = CheckAABBCollision(
                    aTransform.position.x + aCollider.offset.x,
                    aTransform.position.y + aCollider.offset.y,
                    aCollider.width,
                    aCollider.height,
                    bTransform.position.x + bCollider.offset.x,
                    bTransform.position.y + bCollider.offset.x,
                    bCollider.width,
                    bCollider.height);

                if (collisionHappened)
                {
                    Logger::Info("Collision: Entity " + std::to_string(a.GetId()) + " and " + std::to_string(b.GetId()));
                    eventBus->EmitEvent<CollisionEvent>(a, b);

                    // TODO: Emit an event

                }
            }
        }
    }

    bool CheckAABBCollision(
        double aX,
        double aY,
        double aW,
        double aH,
        double bX,
        double bY,
        double bW,
        double bH)
    {
        return (
            aX < bX + bW &&
            aX + aW > bX &&
            aY < bY + bH &&
            aY + aH > bY);
    }
};

*/
#endif