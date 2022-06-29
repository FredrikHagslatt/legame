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

            if(health.healthPercentage <= 0)
            {
                registry.destroy(player);
            }
            registry.destroy(projectile);
        }
    }

    void OnProjectileHitsEnemy(entt::registry &registry, entt::entity &projectile, entt::entity &enemy)
    {
        auto projectileComponent = registry.get<Projectile>(projectile);
        if(projectileComponent.isFriendly)
        {
            auto &health = registry.get<Health>(enemy);
            health.healthPercentage -= projectileComponent.hitPercentDamage;

            if(health.healthPercentage <= 0)
            {
                registry.destroy(enemy);
            }

            registry.destroy(projectile);
        }
    }

    void OnCollision(CollisionEvent event)
    {
        auto &registry = event.registry;
        auto &a = event.entityA;
        auto &b = event.entityB;
        Logger::Info("Damage system received collision event.");

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