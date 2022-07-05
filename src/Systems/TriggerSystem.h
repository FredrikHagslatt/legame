#ifndef TRIGGER_H
#define TRIGGER_H

#include "entt/entt.hpp"
#include "Events/CollisionEvent.h"
#include "Logger/Logger.h"

#include "Components/Tags.h"
#include "Components/SceneSwitcher.h"

class TriggerSystem
{
public:
    static void SwitchScene(std::string scene)
    {
        // Logger::Error(scene);
    }

    static void OnCollision(const CollisionEvent &event)
    {
        auto registry = event.registry;
        auto &a = event.a;
        auto &b = event.b;

        if (registry->all_of<Player_Tag>(a) && registry->all_of<SceneSwitcher>(b))
        {
            SwitchScene("SWITCH");
        }
        if (registry->all_of<Player_Tag>(b) && registry->all_of<SceneSwitcher>(a))
        {
            SwitchScene("SWITCH");
        }
    }
};

#endif