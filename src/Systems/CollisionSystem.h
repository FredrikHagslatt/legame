#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Transform.h"
#include "Components/BoxCollider.h"
#include "Events/CollisionEvent.h"

class CollisionSystem
{
public:
    static bool CheckAABBCollision(
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

    static void Update(entt::registry &registry)
    {
        auto view = registry.view<Transform, BoxCollider>();

        // Fancy nested loop to not check same pair of entities twice.
        for (auto i = view.begin(); i != view.end(); i++)
        {
            entt::entity a = *i;
            for (auto j = i; j != view.end(); j++)
            {
                entt::entity b = *j;

                if (a == b)
                {
                    continue;
                }

                auto aTransform = view.get<Transform>(a);
                auto aCollider = view.get<BoxCollider>(a);

                auto bTransform = view.get<Transform>(b);
                auto bCollider = view.get<BoxCollider>(b);

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
                    // CollisionEvent collisionEvent{a, b};
                    // collisionEventEmitter.publish(collisionEvent);
                }
            }
        }
    }
};

#endif