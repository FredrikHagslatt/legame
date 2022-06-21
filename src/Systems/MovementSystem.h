#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "ECS/ECS.h"
#include "Components/TransformComponent.h"
#include "Components/RigidBodyComponent.h"
#include "EventBus/EventBus.h"
#include "Events/CollisionEvent.h"
#include "Logger/Logger.h"

class MovementSystem : public System
{
public:
    MovementSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void SubscribeToEvents(const std::unique_ptr<EventBus> &eventBus)
    {
        eventBus->SubscribeToEvent<CollisionEvent>(this, &MovementSystem::OnCollision);
    }

    void OnCollision(CollisionEvent &event)
    {
        Entity a = event.a;
        Entity b = event.b;
        Logger::Info("Movement system received collision event between entities: " + std::to_string(a.GetId()) + " and " + std::to_string(b.GetId()) + ".");

        if (a.BelongsToGroup("enemies") && b.BelongsToGroup("obstacles"))
        {
            OnEnemyHitsObstacle(a);
        }
        if (b.BelongsToGroup("enemies") && a.BelongsToGroup("obstacles"))
        {
            OnEnemyHitsObstacle(b);
        }
    }

    void OnEnemyHitsObstacle(Entity enemy)
    {
        if(enemy.HasComponent<RigidBodyComponent>() && enemy.HasComponent<SpriteComponent>())
        {
            auto &rigidBody = enemy.GetComponent<RigidBodyComponent>();
            auto &sprite = enemy.GetComponent<SpriteComponent>();

            if(rigidBody.velocity.x != 0)
            {
                rigidBody.velocity.x *= -1;
                sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            }

            if(rigidBody.velocity.y != 0)
            {
                rigidBody.velocity.y *= -1;
                sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
            }

        }
    }

    void Update(double deltaTime)
    {
        for (auto entity: GetSystemEntities())
        {
            auto &transform = entity.GetComponent<TransformComponent>();
            const auto rigidBody = entity.GetComponent<RigidBodyComponent>();
            transform.position += rigidBody.velocity * float(deltaTime);

                if (entity.HasTag("player")) {
                    int paddingLeft = 10;
                    int paddingTop = 10;
                    int paddingRight = 50;
                    int paddingBottom = 50;
                    transform.position.x = transform.position.x < paddingLeft ? paddingLeft : transform.position.x;
                    transform.position.x = transform.position.x > Game::mapWidth - paddingRight ? Game::mapWidth - paddingRight : transform.position.x;
                    transform.position.y = transform.position.y < paddingTop ? paddingTop : transform.position.y;
                    transform.position.y = transform.position.y > Game::mapHeight - paddingBottom ? Game::mapHeight - paddingBottom : transform.position.y;
                }


            bool isEntityOutsideMap = (
                transform.position.x < 0 ||
                transform.position.x > Game::mapWidth ||
                transform.position.y < 0 ||
                transform.position.y > Game::mapHeight
            );

            if (isEntityOutsideMap && !entity.HasTag("player"))
            {
                entity.Kill();
            }
        }
    }
};

#endif