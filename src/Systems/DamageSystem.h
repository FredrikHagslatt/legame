#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "entt/entt.hpp"
#include "Components/Tags.h"
#include "Components/BoxCollider.h"
#include "Components/Health.h"
#include "Components/Projectile.h"
#include "Components/Health.h"
#include "Events/CollisionEvent.h"

namespace DamageSystem
{
    void OnProjectileHitsPlayer(entt::registry &registry, entt::entity &projectile, entt::entity &player)
    {
        auto projectileComponent = registry.get<Projectile>(projectile);
        if(!projectileComponent.isFriendly)
        {
            auto &health = registry.get<Health>(player);
            health.healthPercentage -= projectileComponent.hitPercentDamage;

            bool playerQueuedForDeath = false;
            bool projectileQueuedForDeath = false;
            for (auto entity : Game::entitiesToKill)
            {
                if (entity == player)
                {
                    playerQueuedForDeath = true;
                }
                if (entity == projectile)
                {
                    projectileQueuedForDeath = true;
                }
            }

            if (!projectileQueuedForDeath)
            {
                Game::entitiesToKill.push_back(projectile);
            }

            if(health.healthPercentage <= 0 && !playerQueuedForDeath)
            {                
                Game::entitiesToKill.push_back(player);
            }

        }
    }

    void OnProjectileHitsEnemy(entt::registry &registry, entt::entity &projectile, entt::entity &enemy)
    {
        auto projectileComponent = registry.get<Projectile>(projectile);
        if(projectileComponent.isFriendly)
        {
            auto &health = registry.get<Health>(enemy);
            health.healthPercentage -= projectileComponent.hitPercentDamage;

            bool enemyQueuedForDeath = false;
            bool projectileQueuedForDeath = false;
            for (auto entity : Game::entitiesToKill)
            {
                if (entity == enemy)
                {
                    enemyQueuedForDeath = true;
                }
                if (entity == projectile)
                {
                    projectileQueuedForDeath = true;
                }
            }

            if (!projectileQueuedForDeath)
            {
                Game::entitiesToKill.push_back(projectile);
            }

            if(health.healthPercentage <= 0 && !enemyQueuedForDeath)
            {                
                Game::entitiesToKill.push_back(enemy);
            }
        }
    }

    void OnCollision(CollisionEvent event)
    {
        auto &registry = event.registry;
        auto &a = event.entityA;
        auto &b = event.entityB;

        if (registry.all_of<Projectile_Tag>(a) && registry.all_of<Player_Tag>(b))
        {
            OnProjectileHitsPlayer(registry, a, b);
        }

        else if (registry.all_of<Projectile_Tag>(b) && registry.all_of<Player_Tag>(a))
        {
            OnProjectileHitsPlayer(registry, b, a);
        }

        else if (registry.all_of<Projectile_Tag>(a) && registry.all_of<Enemy_Tag>(b))
        {
            OnProjectileHitsEnemy(registry, a, b);
        }

        else if (registry.all_of<Projectile_Tag>(b) && registry.all_of<Enemy_Tag>(a))
        {
            OnProjectileHitsEnemy(registry, b, a);
        }
    }

    void Update()
    {

    }
};


#endif