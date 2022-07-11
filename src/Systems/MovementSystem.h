#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Components/Velocity.h"
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

            transform.position.x += velocity.speed * velocity.direction.x * deltaTime;
            transform.position.y += velocity.speed * velocity.direction.y * deltaTime;

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
        auto &playerTransform = registry->get<Transform>(player);
        const auto playerBoxCollider = registry->get<BoxCollider>(player);

        auto &obstacleTransform = registry->get<Transform>(obstacle);
        const auto obstacleBoxCollider = registry->get<BoxCollider>(obstacle);

        vec2f maxDisplacement;
        if (playerTransform.position.x < obstacleTransform.position.x)
        {
            maxDisplacement.x = obstacleTransform.position.x - playerTransform.position.x - playerBoxCollider.width;
        }
        else
        {
            maxDisplacement.x = playerTransform.position.x - obstacleTransform.position.x - obstacleBoxCollider.width;
        }

        if (playerTransform.position.y < obstacleTransform.position.y)
        {
            maxDisplacement.y = obstacleTransform.position.y - playerTransform.position.y - playerBoxCollider.height;
        }
        else
        {
            maxDisplacement.y = playerTransform.position.y - obstacleTransform.position.y - obstacleBoxCollider.height;
        }

        vec2f diff = obstacleTransform.position - playerTransform.position;
        double displacementAngle = diff.arg();

        vec2f displacement;
        if (maxDisplacement.y < maxDisplacement.x * tan(displacementAngle))
        {
            displacement = vec2f(maxDisplacement.y / tan(displacementAngle), maxDisplacement.y);
        }
        else
        {
            displacement = vec2f(maxDisplacement.x, maxDisplacement.x * tan(displacementAngle));
        }

        playerTransform.position = playerTransform.position + displacement;

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