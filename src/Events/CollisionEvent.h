#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "entt/entt.hpp"

class CollisionEvent
{
public:
    entt::registry &registry;
    entt::entity a;
    entt::entity b;
    CollisionEvent(entt::registry &registry, entt::entity a, entt::entity b) : registry(registry), a(a), b(b) {}
};

#endif
