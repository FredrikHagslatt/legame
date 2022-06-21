#ifndef RENDERHEALTHSYSTEM_H
#define RENDERHEALTHSYSTEM_H

#include "ECS/ECS.h"
#include "AssetStore/AssetStore.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/HealthComponent.h"
#include <SDL2/SDL.h>


class RenderHealthSystem : public System
{
public:
    RenderHealthSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
        RequireComponent<HealthComponent>();
    }


    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore> &assetStore, SDL_Rect &camera)
    {
        SDL_Color healthBarColor = {255, 255, 255};
        SDL_Color red = {255, 0, 0};
        SDL_Color yellow = {255, 255, 0};
        SDL_Color green = {0, 255, 0};

        for (auto entity : GetSystemEntities())
        {
            const auto transform = entity.GetComponent<TransformComponent>();
            const auto sprite = entity.GetComponent<SpriteComponent>();
            const auto health = entity.GetComponent<HealthComponent>();

            if(health.healthPercentage >= 0 && health.healthPercentage < 40)
            {
                healthBarColor = red;
            }

            else if(health.healthPercentage >= 40 && health.healthPercentage < 80)
            {
                healthBarColor = yellow;
            }

            else if(health.healthPercentage >= 80)
            {
                healthBarColor = green;
            }

            int healthBarWidth = 15;
            int healthBarHeight = 3;
            glm::vec2 healthBarPos = 
            {
                transform.position.x + (sprite.width * transform.scale.x) - camera.x,
                transform.position.y - camera.y
            };

            SDL_Rect healthBarRect = 
            {
                static_cast<int>(healthBarPos.x),
                static_cast<int>(healthBarPos.y),
                static_cast<int>(healthBarWidth * (health.healthPercentage / 100.0)),
                static_cast<int>(healthBarHeight)
            };

            SDL_SetRenderDrawColor(renderer, healthBarColor.r, healthBarColor.g, healthBarColor.b, 255);
            SDL_RenderFillRect(renderer, &healthBarRect);

            // Render the health percentage text label indicator
            std::string healthText = std::to_string(health.healthPercentage);
            SDL_Surface* surface = TTF_RenderText_Blended(assetStore->GetFont("pico8-font-5"), healthText.c_str(), healthBarColor);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            int labelWidth = 0;
            int labelHeight = 0;
            SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);
            SDL_Rect healthBarTextRect = {
                static_cast<int>(healthBarPos.x),
                static_cast<int>(healthBarPos.y) + 5,
                labelWidth,
                labelHeight
            };
            
            SDL_RenderCopy(renderer, texture, NULL, &healthBarTextRect);
            SDL_DestroyTexture(texture);

        }
    }

};

#endif