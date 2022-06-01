#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

class RenderSystem : public System
{
public:
    RenderSystem()
    {
        // TODO: Require SpriteComponent
    }

    void Update()
    {
        //Loop all entities that the system is interrested in
        for (auto entity: GetEntities())
        {
            //RenderSprite
        }
    }
};

#endif