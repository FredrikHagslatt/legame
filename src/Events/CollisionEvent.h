#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "entt/entt.hpp"
#include <memory>

struct CollisionEvent
{
    std::shared_ptr<entt::registry> registry;
    entt::entity a;
    entt::entity b;
};

#endif
