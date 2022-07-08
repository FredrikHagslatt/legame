#ifndef TRIGGER_H
#define TRIGGER_H

#include <string>

#include "entt/entt.hpp"
#include "Events/CollisionEvent.h"
#include "Logger/Logger.h"

#include "Components/Tags.h"
#include "Components/SceneSwitcher.h"

#include "Events/SceneSwitchEvent.h"

class TriggerSystem
{
public:
    static void SwitchScene(std::string sceneManagerId, std::string sceneName)
    {
        Event::dispatcher.trigger(SceneSwitchEvent{sceneManagerId, sceneName});
    }

    static void OnCollision(const CollisionEvent &event)
    {
        auto registry = event.registry;
        auto &a = event.a;
        auto &b = event.b;

        if (registry->all_of<Player_Tag>(a) && registry->all_of<SceneSwitcher>(b))
        {
            auto sceneSwitcher = registry->get<SceneSwitcher>(b);
            SwitchScene(sceneSwitcher.sceneManagerId, sceneSwitcher.sceneName);
        }
        if (registry->all_of<Player_Tag>(b) && registry->all_of<SceneSwitcher>(a))
        {
            auto sceneSwitcher = registry->get<SceneSwitcher>(a);
            SwitchScene(sceneSwitcher.sceneManagerId, sceneSwitcher.sceneName);
        }
    }
};

#endif