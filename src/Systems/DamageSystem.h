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

/*
    void OnProjectileHitsPlayer(Entity projectile, Entity player)
    {
        auto projectileComponent = projectile.GetComponent<ProjectileComponent>();
        if(!projectileComponent.isFriendly)
        {
            auto &health = player.GetComponent<HealthComponent>();
            health.healthPercentage -= projectile.hitPercentDamage;

            if(health.healthPercentage <= 0)
            {
                player.Kill();
            }
            projectile.Kill();
        }
    }

    void OnProjectileHitsEnemy(Entity projectile, Entity enemy)
    {
        auto projectileComponent = projectile.GetComponent<ProjectileComponent>();
        if(projectileComponent.isFriendly)
        {
            auto &health = enemy.GetComponent<HealthComponent>();
            health.healthPercentage -= projectile.hitPercentDamage;

            if(health.healthPercentage <= 0)
            {
                enemy.Kill();
            }
            projectile.Kill();
        }
    }
*/

    void OnCollision(CollisionEvent event)
    {
        auto &registry = event.registry;
        auto &a = event.entityA;
        auto &b = event.entityB;
        Logger::Info("Damage system received collision event.");

        if (registry.all_of<Projectile_Tag>(a) && registry.all_of<Player_Tag>(b))
        {
            Logger::Error(" HIT ");
        }

/*
        if (a.BelongsToGroup("projectiles") && b.HasTag("player"))
        {        
            OnProjectileHitsPlayer(a, b);
        }

        if (b.BelongsToGroup("projectiles") && a.HasTag("player"))
        {
            OnProjectileHitsPlayer(b, a);
        }

        if (a.BelongsToGroup("projectiles") && b.BelongsToGroup("enemies"))
        {
            OnProjectileHitsEnemy(a, b);
        }
        if (b.BelongsToGroup("projectiles") && a.BelongsToGroup("enemies"))
        {
            OnProjectileHitsEnemy(b, a);
        }
*/
    }

    void Update()
    {

    }
};


#endif