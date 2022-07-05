#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "entt/entt.hpp"
#include "Components/Tags.h"
#include "Components/BoxCollider.h"
#include "Components/Health.h"
#include "Components/Projectile.h"
#include "Components/Health.h"
#include "Events/CollisionEvent.h"

extern std::list<entt::entity> entitiesToKill;
class DamageSystem
{
public:
    static void OnProjectileHitsPlayer(std::shared_ptr<entt::registry> registry, entt::entity &projectile, entt::entity &player)
    {
        auto projectileComponent = registry->get<Projectile>(projectile);
        if (!projectileComponent.isFriendly)
        {
            auto &health = registry->get<Health>(player);
            health.healthPercentage -= projectileComponent.hitPercentDamage;

            bool playerQueuedForDeath = false;
            bool projectileQueuedForDeath = false;
            for (auto entity : entitiesToKill)
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
                entitiesToKill.push_back(projectile);
            }

            if (health.healthPercentage <= 0 && !playerQueuedForDeath)
            {
                entitiesToKill.push_back(player);
            }
        }
    }

    static void OnProjectileHitsEnemy(std::shared_ptr<entt::registry> registry, entt::entity &projectile, entt::entity &enemy)
    {
        auto projectileComponent = registry->get<Projectile>(projectile);
        if (projectileComponent.isFriendly)
        {
            auto &health = registry->get<Health>(enemy);
            health.healthPercentage -= projectileComponent.hitPercentDamage;

            bool enemyQueuedForDeath = false;
            bool projectileQueuedForDeath = false;
            for (auto entity : entitiesToKill)
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
                entitiesToKill.push_back(projectile);
            }

            if (health.healthPercentage <= 0 && !enemyQueuedForDeath)
            {
                entitiesToKill.push_back(enemy);
            }
        }
    }

    static void OnCollision(const CollisionEvent event)
    {
        auto registry = event.registry;
        auto a = event.a;
        auto b = event.b;

        if (registry->all_of<Projectile_Tag>(a) && registry->all_of<Player_Tag>(b))
        {
            OnProjectileHitsPlayer(registry, a, b);
        }

        else if (registry->all_of<Projectile_Tag>(b) && registry->all_of<Player_Tag>(a))
        {
            OnProjectileHitsPlayer(registry, b, a);
        }

        else if (registry->all_of<Projectile_Tag>(a) && registry->all_of<Enemy_Tag>(b))
        {
            OnProjectileHitsEnemy(registry, a, b);
        }

        else if (registry->all_of<Projectile_Tag>(b) && registry->all_of<Enemy_Tag>(a))
        {
            OnProjectileHitsEnemy(registry, b, a);
        }
    }

    static void Update()
    {
    }
};

#endif