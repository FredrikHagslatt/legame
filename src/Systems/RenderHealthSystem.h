#ifndef RENDERHEALTHSYSTEM_H
#define RENDERHEALTHSYSTEM_H

#include "entt/entt.hpp"
#include "AssetStore/AssetStore.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Components/Health.h"
#include <SDL2/SDL.h>

class RenderHealthSystem
{
public:
    static void Update(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore, SDL_Rect &camera)
    {
        SDL_Color healthBarColor = {255, 255, 255};
        SDL_Color red = {255, 0, 0};
        SDL_Color yellow = {255, 255, 0};
        SDL_Color green = {0, 255, 0};

        auto view = registry->view<Transform, Sprite, Health>();

        for (auto entity : view)
        {
            const auto transform = view.get<Transform>(entity);
            const auto sprite = view.get<Sprite>(entity);
            const auto health = view.get<Health>(entity);

            if (health.hitPoints >= 0 && health.hitPoints < 40)
            {
                healthBarColor = red;
            }

            else if (health.hitPoints >= 40 && health.hitPoints < 80)
            {
                healthBarColor = yellow;
            }

            else if (health.hitPoints >= 80)
            {
                healthBarColor = green;
            }

            int healthBarWidth = 15;
            int healthBarHeight = 3;
            vec2f healthBarPos =
                {
                    transform.position.x + (sprite.width * transform.scale.x) - camera.x,
                    transform.position.y - camera.y};

            SDL_Rect healthBarRect =
                {
                    static_cast<int>(healthBarPos.x),
                    static_cast<int>(healthBarPos.y),
                    static_cast<int>(healthBarWidth * (health.hitPoints / 100.0)),
                    static_cast<int>(healthBarHeight)};

            SDL_SetRenderDrawColor(renderer, healthBarColor.r, healthBarColor.g, healthBarColor.b, 255);
            SDL_RenderFillRect(renderer, &healthBarRect);

            // Render the health percentage text label indicator
            std::string healthText = std::to_string(health.hitPoints);
            SDL_Surface *surface = TTF_RenderText_Blended(assetStore->GetFont("pico8-font-5"), healthText.c_str(), healthBarColor);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            int labelWidth = 0;
            int labelHeight = 0;
            SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);
            SDL_Rect healthBarTextRect = {
                static_cast<int>(healthBarPos.x),
                static_cast<int>(healthBarPos.y) + 5,
                labelWidth,
                labelHeight};

            SDL_RenderCopy(renderer, texture, NULL, &healthBarTextRect);
            SDL_DestroyTexture(texture);
        }
    }
};

#endif