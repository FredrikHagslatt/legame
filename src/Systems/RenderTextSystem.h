#ifndef RENDERTEXTSYSTEM_H
#define RENDERTEXTSYSTEM_H

#include "Types.h"
#include "entt/entt.hpp"
#include "Components/TextLabel.h"
#include "AssetStore/AssetStore.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Logger/Logger.h"

class RenderTextSystem
{
public:
    static vec2f GetTextDimensions(SDL_Renderer *renderer, std::string text, TTF_Font *font)
    {
        SDL_Color color = {0, 0, 0};
        SDL_Surface *surface = TTF_RenderText_Blended(
            font,
            text.c_str(),
            color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        int textureWidth = 0;
        int textureHeight = 0;
        SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
        SDL_DestroyTexture(texture);
        return {static_cast<float>(textureWidth), static_cast<float>(textureHeight)};
    }

    static void Update(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore, const SDL_Rect &camera)
    {
        auto view = registry->view<TextLabel>();
        for (auto entity : view)
        {
            const auto textLabel = view.get<TextLabel>(entity);

            SDL_Surface *surface = TTF_RenderText_Blended(
                assetStore->GetFont(textLabel.assetId),
                textLabel.text.c_str(),
                textLabel.color);

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            int labelWidth = 0;
            int labelHeight = 0;
            SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

            SDL_Rect dstRect =
                {
                    static_cast<int>(textLabel.position.x - (textLabel.isFixed ? 0 : camera.x)),
                    static_cast<int>(textLabel.position.y - (textLabel.isFixed ? 0 : camera.y)),
                    labelWidth,
                    labelHeight};
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_DestroyTexture(texture);
        }
    }
};

#endif