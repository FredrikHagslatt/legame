#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

class MovementSystem : public System
{
public:
    MovementSystem()
    {
        // TODO: Require TransformComponent
        // TODO: Require VelocityComponent
    }

    void Update()
    {
        //Loop all entities that the system is interrested in
        for (auto entity: GetEntities())
        {
            //Update entity position based on velocity
        }
    }
};

#endif