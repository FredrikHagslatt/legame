#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "entt/entt.hpp"

struct CollisionEvent
{
    entt::registry &registry;
    entt::entity &entityA;
    entt::entity &entityB;
};

entt::sigh<void(CollisionEvent)> CollisionEventEmitter;
entt::sink CollisionEventListener{CollisionEventEmitter};

#endif