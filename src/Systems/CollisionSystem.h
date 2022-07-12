#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Transform.h"
#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"

#include "Events/EventDispatcher.h"
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

    static void UpdateRectangleVsRectangle(std::shared_ptr<entt::registry> registry)
    {
        auto view = registry->view<Transform, BoxCollider>();

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
                    bTransform.position.y + bCollider.offset.y,
                    bCollider.width,
                    bCollider.height);

                if (collisionHappened)
                {
                    Event::dispatcher.trigger(CollisionEvent{registry, a, b});
                }
            }
        }
    }

    static void UpdateCircleVsRectangle(std::shared_ptr<entt::registry> registry)
    {
        auto circleView = registry->view<Transform, CircleCollider>();
        auto boxView = registry->view<Transform, BoxCollider>();

        for (auto circle : circleView)
        {
            auto &circleTransform = circleView.get<Transform>(circle);
            const auto circleCollider = circleView.get<CircleCollider>(circle);

            vec2f circleColliderPos = circleTransform.position + circleCollider.offset;

            for (auto box : boxView)
            {
                const auto boxTransform = boxView.get<Transform>(box);
                const auto boxCollider = boxView.get<BoxCollider>(box);

                float boxLeftEdge = boxTransform.position.x + boxCollider.offset.x;
                float boxRightEdge = boxLeftEdge + boxCollider.width;
                float boxTopEdge = boxTransform.position.y + boxCollider.offset.y;
                float boxBotEdge = boxTopEdge + boxCollider.height;

                vec2f circleToBox;
                circleToBox.x = std::max(boxLeftEdge, std::min(boxRightEdge, circleColliderPos.x)) - circleColliderPos.x;
                circleToBox.y = std::max(boxTopEdge, std::min(boxBotEdge, circleColliderPos.y)) - circleColliderPos.y;

                if (circleToBox.magnitudePow2() < circleCollider.radius * circleCollider.radius)
                {
                    Event::dispatcher.trigger(CollisionEvent{registry, circle, box});
                }
            }
        }
    }

    static void UpdateCircleVsCircle(std::shared_ptr<entt::registry> registry)
    {
    }

    static void Update(std::shared_ptr<entt::registry> registry)
    {
        UpdateRectangleVsRectangle(registry);
        UpdateCircleVsRectangle(registry);
        UpdateCircleVsCircle(registry);
    }
};

#endif