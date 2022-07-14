#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Components/Velocity.h"
#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"
#include "Events/CollisionEvent.h"
#include "Logger/Logger.h"
#include "Game/Game.h"

class MovementSystem
{
public:
    static void Update(std::shared_ptr<entt::registry> registry, double deltaTime)
    {
        auto view = registry->view<Transform, Velocity>();
        for (auto entity : view)
        {
            auto &transform = view.get<Transform>(entity);
            const auto &velocity = view.get<Velocity>(entity);

            if (velocity.direction.x != 0 && velocity.direction.y != 0)
            { // Reduce diagonal speed to match hor/vert speed
                transform.position += velocity.direction * velocity.speed * deltaTime * 0.707;
            }
            else
            {
                transform.position += velocity.direction * velocity.speed * deltaTime;
            }

            if (registry->all_of<StayOnMap_Tag>(entity))
            {
                int paddingLeft = 10;
                int paddingTop = 10;
                int paddingRight = 50;
                int paddingBottom = 50;
                transform.position.x = transform.position.x < paddingLeft ? paddingLeft : transform.position.x;
                transform.position.x = transform.position.x > Game::mapWidth - paddingRight ? Game::mapWidth - paddingRight : transform.position.x;
                transform.position.y = transform.position.y < paddingTop ? paddingTop : transform.position.y;
                transform.position.y = transform.position.y > Game::mapHeight - paddingBottom ? Game::mapHeight - paddingBottom : transform.position.y;
            }

            bool isEntityOutsideMap = (transform.position.x < 0 ||
                                       transform.position.x > Game::mapWidth ||
                                       transform.position.y < 0 ||
                                       transform.position.y > Game::mapHeight);

            if (isEntityOutsideMap && !registry->all_of<Player_Tag>(entity))
            {
                registry->destroy(entity);
                Logger::Info("[MovementSystem] Killing entity");
            }
        }
    }

    static void OnEnemyHitsObstacle(std::shared_ptr<entt::registry> registry, entt::entity enemy)
    {

        if (registry->all_of<Velocity, Sprite>(enemy))
        {
            auto &velocity = registry->get<Velocity>(enemy);
            auto &sprite = registry->get<Sprite>(enemy);

            if (velocity.direction.x != 0)
            {
                velocity.direction.x *= -1;
                sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            }

            if (velocity.direction.y != 0)
            {
                velocity.direction.y *= -1;
                sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
            }
        }
    }

    static void OnPlayerHitsObstacle(std::shared_ptr<entt::registry> registry, entt::entity player, entt::entity obstacle)
    {
        Logger::Info("Player hit obstacle");
        auto &circleTransform = registry->get<Transform>(player);
        const auto circleCollider = registry->get<CircleCollider>(player);
        vec2f circleColliderPos = circleTransform.position + circleCollider.offset;

        const auto boxTransform = registry->get<Transform>(obstacle);
        const auto boxCollider = registry->get<BoxCollider>(obstacle);

        float boxLeftEdge = boxTransform.position.x + boxCollider.offset.x;
        float boxRightEdge = boxLeftEdge + boxCollider.width;
        float boxTopEdge = boxTransform.position.y + boxCollider.offset.y;
        float boxBotEdge = boxTopEdge + boxCollider.height;

        vec2f circleToBox;
        circleToBox.x = std::max(boxLeftEdge, std::min(boxRightEdge, circleColliderPos.x)) - circleColliderPos.x;
        circleToBox.y = std::max(boxTopEdge, std::min(boxBotEdge, circleColliderPos.y)) - circleColliderPos.y;

        float distCircleToBox = circleToBox.magnitude();
        float overlap = circleCollider.radius - distCircleToBox;

        circleTransform.position.x -= circleToBox.x * overlap / distCircleToBox;
        circleTransform.position.y -= circleToBox.y * overlap / distCircleToBox;
    }

    static void OnCollision(CollisionEvent event)
    {
        auto registry = event.registry;
        auto &a = event.a;
        auto &b = event.b;

        if (registry->all_of<Enemy_Tag>(a) && registry->all_of<Obstacle_Tag>(b))
        {
            OnEnemyHitsObstacle(registry, a);
        }

        else if (registry->all_of<Enemy_Tag>(b) && registry->all_of<Obstacle_Tag>(a))
        {
            OnEnemyHitsObstacle(registry, b);
        }

        else if (registry->all_of<Player_Tag>(a) && registry->all_of<Obstacle_Tag>(b))
        {
            OnPlayerHitsObstacle(registry, a, b);
        }

        else if (registry->all_of<Player_Tag>(b) && registry->all_of<Obstacle_Tag>(a))
        {
            OnPlayerHitsObstacle(registry, b, a);
        }
    }
};

#endif