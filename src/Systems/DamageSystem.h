#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "entt/entt.hpp"
#include "Components/BoxCollider.h"
#include "Components/Health.h"
#include "Components/Projectile.h"
#include "Components/Health.h"
#include "EventBus/EventBus.h"
#include "Events/CollisionEvent.h"
/*

class DamageSystem : public System
{
public:
    DamageSystem()
    {
        RequireComponent<BoxColliderComponent>();
    }

    void SubscribeToEvents(std::unique_ptr<EventBus> &eventBus)
    {
        eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
    }

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

    void OnCollision(CollisionEvent &event)
    {
        Entity a = event.a;
        Entity b = event.b;
        Logger::Info("Damage system received collision event between entities: " + std::to_string(a.GetId()) + " and " + std::to_string(b.GetId()) + ".");

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
    }

    void Update()
    {

    }
};

*/

#endif