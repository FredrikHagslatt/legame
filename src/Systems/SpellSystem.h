#ifndef SPELLSYSTEM_H
#define SPELLSYSTEM_H

#include "Components/ArsenalSpell.h"
#include "Components/LifeTime.h"
#include "Components/Transform.h"
#include "Components/Tags.h"

#include "Systems/ProjectileEmitSystem.h" // For GetProjectileSpawnPosition();

#include "entt/entt.hpp"
#include "Logger/Logger.h"

class SpellSystem
{
public:
    static void Update(std::shared_ptr<entt::registry> registry, float elapsedTime)
    {

        auto view = registry->view<ArsenalSpell>();

        for (auto entity : view)
        {
            auto &spellSpecs = view.get<ArsenalSpell>(entity);

            if (spellSpecs.cooldownRemaining >= 0.0f)
            {
                spellSpecs.cooldownRemaining -= elapsedTime;
            }
        }
    }

    /*
        Spell content checklist
        Transform
        Animation
        Sound
        Damage (can be 0)

        Optional:
        effectVector
        Velocity
        etc..
    */

    static vec2f GetCrosshairPos(std::shared_ptr<entt::registry> registry)
    {
        auto crosshairView = registry->view<Crosshair_Tag, Transform, Sprite>();

        for (auto crosshair : crosshairView)
        {
            const auto transform = crosshairView.get<Transform>(crosshair);
            return transform.position;
        }
        return vec2f(0);
    }

    static void CastFireball(std::shared_ptr<entt::registry> registry, entt::entity caster)
    {
        Logger::Info("Casting Fireball");
        const unsigned int speed = 1800;
        const unsigned int damage = 40;
        const unsigned int duration = 500;
        const unsigned int fireball_width = 16;

        vec2f target(0);
        if (registry->all_of<Player_Tag>(caster))
        {
            target = GetCrosshairPos(registry);
            target.x -= SCALE * fireball_width / 2;
            target.y -= SCALE * fireball_width / 2;
        }

        vec2f spawnPosition = ProjectileEmitSystem::GetProjectileSpawnPosition(registry, caster);

        vec2f direction = target - spawnPosition;
        direction = direction / direction.magnitude();

        auto fireBall = registry->create();
        registry->emplace<Projectile_Tag>(fireBall);
        registry->emplace<Transform>(fireBall, spawnPosition, vec2f(1.0, 1.0), 0.0);
        registry->emplace<Velocity>(fireBall, speed, direction);
        registry->emplace<Sprite>(fireBall, "fireball-spritesheet", 16, 10);
        registry->emplace<Animation>(fireBall, 4, 16, true, false);

        registry->emplace<CircleCollider>(fireBall, fireball_width);
        registry->emplace<Projectile>(fireBall, true, damage, duration);

        // Get the components needed for spell casting
        // auto &spellSpecs = view.get<ArsenalSpell>(entity);
        // Animation &animationComponent = view.get<Animation>(entity);
        // Sound &soundComponent = view.get<SoundComponent>();
        // Damage &damageComponent = entity.get<DamageComponent>();
        // EffectVector &effectVector = entity.get<EffectComponent>();

        // Play the spell animation
        // animationComponent.PlayAnimation(spellComponent.animationName);
        // Spawn an entity with the animation instead /F

        // Play the spell sound
        // soundComponent.PlaySound(spellComponent.soundName);

        // Apply damage to the target
        // ApplyDamage(entity);
        // Spawn spell entity instead

        // Apply effects to the target
        // ApplyEffects(entity);
        // Spawn spell entity instead
    }

    static void CastBlink(std::shared_ptr<entt::registry> registry, entt::entity caster)
    {
        Logger::Info("Casting Blink");
        const unsigned int range = 400;

        auto &transform = registry->get<Transform>(caster);
        auto &sprite = registry->get<Sprite>(caster);

        auto blinkSmoke = registry->create();
        registry->emplace<Transform>(blinkSmoke, transform.position, vec2f(1.0, 1.0), 0.0);
        registry->emplace<Sprite>(blinkSmoke, "blinkSmoke-image", 16, 32);
        registry->emplace<Animation>(blinkSmoke, 4, 8, false, false);
        registry->emplace<LifeTime>(blinkSmoke, 500);

        vec2f target(0);
        if (registry->all_of<Player_Tag>(caster))
        {
            target = GetCrosshairPos(registry);
        }

        vec2f blinkVector = target - transform.position;
        float blinkDistance = blinkVector.magnitude();
        if (blinkDistance > range)
        {
            blinkVector = blinkVector * range / blinkDistance;
            target += blinkVector;
        }

        target.x -= (sprite.width / 2) * transform.scale.x;
        target.y -= (sprite.pivotPoint) * transform.scale.y;
        transform.position = target;

        // Get the components needed for spell casting
        // auto &spellSpecs = view.get<ArsenalSpell>(entity);
    }

    static void OnKeyPressed(std::shared_ptr<entt::registry> registry, const KeyPressedEvent event)
    {
        if (event.keycode == SDLK_1)
        {
            auto view = registry->view<ArsenalSpell>();

            auto playerView = registry->view<Player_Tag>();
            for (auto player : playerView)
            {
                CastFireball(registry, player);
            }

            for (auto entity : view)
            {
                auto &spell = view.get<ArsenalSpell>(entity);
                // Add logic for choosing spell here

                if (spell.cooldownRemaining <= 0.0f)
                {
                    // Perform spell casting logic
                    // auto playerView = registry->view<Player_Tag>();
                    // for (auto player : view)
                    // {
                    //     CastFireball(registry, player);
                    // }

                    // Start the spell cooldownRemaining
                    spell.cooldownRemaining = spell.cooldownTotal;
                }
            }
        }
        if (event.keycode == SDLK_3)
        {
            auto playerView = registry->view<Player_Tag>();
            for (auto player : playerView)
            {
                CastBlink(registry, player);
            }
        }
    }
};
#endif