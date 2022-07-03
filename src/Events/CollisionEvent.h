#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "entt/entt.hpp"

class CollisionEvent
{
public:
    entt::entity a;
    entt::entity b;
    CollisionEvent(entt::entity a, entt::entity b) : a(a), b(b) {}
};

#endif
