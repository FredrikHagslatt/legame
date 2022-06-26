#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "entt/entt.hpp"

struct CollisionEvent
{
    entt::registry &registry;
    entt::entity &a;
    entt::entity &b;
};

entt::sigh<void(CollisionEvent)> CollisionEventEmitter;
entt::sink CollisionEventListener{CollisionEventEmitter};

#endif