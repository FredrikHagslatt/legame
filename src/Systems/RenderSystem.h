#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "entt/entt.hpp"
#include "Components/Tags.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "AssetStore/AssetStore.h"
#include <SDL2/SDL.h>

class RenderSystem
{
private:
    static bool IsEntityOutsideCameraview(const Transform transform, const Sprite sprite, SDL_Rect &camera)
    {
        return (transform.position.x + (transform.scale.x * sprite.width) < camera.x ||
                transform.position.x > camera.x + camera.w ||
                transform.position.y + (transform.scale.y * sprite.height) < camera.y ||
                transform.position.y > camera.y + camera.h);
    }

    static void RenderEntity(const Transform transform, const Sprite sprite, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore, SDL_Rect &camera)
    {
        SDL_Rect srcRect = sprite.srcRect;
        SDL_Rect dstRect =
            {
                static_cast<int>(transform.position.x - (sprite.fixedPosition ? 0 : camera.x)),
                static_cast<int>(transform.position.y - (sprite.fixedPosition ? 0 : camera.y)),
                static_cast<int>(sprite.width * transform.scale.x),
                static_cast<int>(sprite.height * transform.scale.y)};

        SDL_RenderCopyEx(
            renderer,
            assetStore->GetTexture(sprite.assetId),
            &srcRect,
            &dstRect,
            transform.rotation,
            NULL,
            sprite.flip);
    }

    static void RenderTiles(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore, SDL_Rect &camera)
    {
        auto view = registry->view<Transform, Sprite, Tile_Tag>();

        for (auto entity : view)
        {

            const auto &sprite = view.get<Sprite>(entity);
            const auto &transform = view.get<Transform>(entity);

            if (IsEntityOutsideCameraview(transform, sprite, camera))
            {
                continue;
            }

            RenderEntity(transform, sprite, renderer, assetStore, camera);
        }
    }

    static void RenderGrounded(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore, SDL_Rect &camera)
    {
        struct RenderableEntity
        {
            Transform transform;
            Sprite sprite;
        };
        std::vector<RenderableEntity> renderableEntities;

        auto view = registry->view<Transform, Sprite>(entt::exclude<Tile_Tag, Airborne_Tag, Effect_Tag, UI_Tag>);
        for (auto entity : view)
        {
            RenderableEntity renderableEntity;
            renderableEntity.sprite = view.get<Sprite>(entity);
            renderableEntity.transform = view.get<Transform>(entity);

            if (IsEntityOutsideCameraview(renderableEntity.transform, renderableEntity.sprite, camera) && !renderableEntity.sprite.fixedPosition)
            {
                continue;
            }
            renderableEntities.emplace_back(renderableEntity);
        }

        std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity &a, const RenderableEntity &b)
                  { return a.transform.position.y + a.sprite.pivotPoint < b.transform.position.y + b.sprite.pivotPoint; });

        for (auto entity : renderableEntities)
        {
            RenderEntity(entity.transform, entity.sprite, renderer, assetStore, camera);
        }
    }

    static void RenderAirborne(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore, SDL_Rect &camera)
    {
        auto view = registry->view<Transform, Sprite, Airborne_Tag>();

        for (auto entity : view)
        {
            const auto &sprite = view.get<Sprite>(entity);
            const auto &transform = view.get<Transform>(entity);

            if (IsEntityOutsideCameraview(transform, sprite, camera) && !sprite.fixedPosition)
            {
                continue;
            }

            RenderEntity(transform, sprite, renderer, assetStore, camera);
        }
    }

    static void RenderEffects(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore, SDL_Rect &camera)
    {
        auto view = registry->view<Transform, Sprite, Effect_Tag>();

        for (auto entity : view)
        {
            const auto &sprite = view.get<Sprite>(entity);
            const auto &transform = view.get<Transform>(entity);

            if (IsEntityOutsideCameraview(transform, sprite, camera) && !sprite.fixedPosition)
            {
                continue;
            }

            RenderEntity(transform, sprite, renderer, assetStore, camera);
        }
    }

    static void RenderUI(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore, SDL_Rect &camera)
    {
        auto view = registry->view<Transform, Sprite, UI_Tag>();

        for (auto entity : view)
        {
            const auto &sprite = view.get<Sprite>(entity);
            const auto &transform = view.get<Transform>(entity);

            if (IsEntityOutsideCameraview(transform, sprite, camera) && !sprite.fixedPosition)
            {
                continue;
            }

            RenderEntity(transform, sprite, renderer, assetStore, camera);
        }
    }

public:
    static void Update(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore, SDL_Rect &camera)
    {
        RenderTiles(registry, renderer, assetStore, camera);
        RenderGrounded(registry, renderer, assetStore, camera);
        RenderAirborne(registry, renderer, assetStore, camera);
        RenderEffects(registry, renderer, assetStore, camera);
        RenderUI(registry, renderer, assetStore, camera);
    }
};

#endif