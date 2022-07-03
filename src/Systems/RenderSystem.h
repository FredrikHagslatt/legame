#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "AssetStore/AssetStore.h"
#include <SDL2/SDL.h>

extern SDL_Renderer *renderer;
extern AssetStore assetStore;
extern entt::registry registry;
class RenderSystem
{
public:
    static void Update(SDL_Rect &camera)
    {
        struct RenderableEntity
        {
            Transform transform;
            Sprite sprite;
        };
        std::vector<RenderableEntity> renderableEntities;

        auto view = registry.view<Transform, Sprite>();
        for (auto entity : view)
        {
            RenderableEntity renderableEntity;
            renderableEntity.sprite = view.get<Sprite>(entity);
            renderableEntity.transform = view.get<Transform>(entity);

            bool isEntityOutsideCameraView =
                (renderableEntity.transform.position.x + (renderableEntity.transform.scale.x * renderableEntity.sprite.width) < camera.x ||
                 renderableEntity.transform.position.x > camera.x + camera.w ||
                 renderableEntity.transform.position.y + (renderableEntity.transform.scale.y * renderableEntity.sprite.height) < camera.y ||
                 renderableEntity.transform.position.y > camera.y + camera.h);

            if (isEntityOutsideCameraView && !renderableEntity.sprite.fixedPosition)
            {
                continue;
            }
            renderableEntities.emplace_back(renderableEntity);
        }

        std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity &a, const RenderableEntity &b)
                  { return a.sprite.zIndex < b.sprite.zIndex; });

        for (auto entity : renderableEntities)
        {
            const auto transform = entity.transform;
            const auto sprite = entity.sprite;

            SDL_Rect srcRect = sprite.srcRect;
            SDL_Rect dstRect =
                {
                    static_cast<int>(transform.position.x - (sprite.fixedPosition ? 0 : camera.x)),
                    static_cast<int>(transform.position.y - (sprite.fixedPosition ? 0 : camera.y)),
                    static_cast<int>(sprite.width * transform.scale.x),
                    static_cast<int>(sprite.height * transform.scale.y)};

            SDL_RenderCopyEx(
                renderer,
                assetStore.GetTexture(sprite.assetId),
                &srcRect,
                &dstRect,
                transform.rotation,
                NULL,
                sprite.flip);
        }
    }
};

#endif