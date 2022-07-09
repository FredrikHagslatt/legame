#include "AssetStore.h"
#include "Logger/Logger.h"
#include <SDL2/SDL_image.h>

AssetStore::AssetStore()
{
    Logger::Info("[AssetStore] Asset Store Created.");
}

AssetStore::~AssetStore()
{
    ClearAssets();
    Logger::Info("[AssetStore] Asset Store Destroyed.");
}

void AssetStore::ClearAssets()
{
    for (auto texture : textures)
    {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();

    for (auto font : fonts)
    {
        TTF_CloseFont(font.second);
    }
    fonts.clear();

    // TODO: Clear all audio
}

void AssetStore::AddTexture(SDL_Renderer *renderer, const std::string &assetId, const std::string &filePath)
{
    SDL_Surface *surface = IMG_Load(filePath.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    textures.emplace(assetId, texture);
    Logger::Info("[AssetStore] Texture with assetId: '" + assetId + "' added");
}

SDL_Texture *AssetStore::GetTexture(const std::string &assetId) const
{
    if (!textures.count(assetId))
    {
        Logger::Fatal("[AssetStore] Missing texture with ID: '" + assetId + "'");
    }
    return textures.at(assetId);
}

void AssetStore::AddFont(const std::string &assetId, const std::string &filePath, int fontSize)
{
    fonts.emplace(assetId, TTF_OpenFont(filePath.c_str(), fontSize));
    Logger::Info("[AssetStore] Font with assetId: '" + assetId + "' added");
}

TTF_Font *AssetStore::GetFont(const std::string assetId) const
{
    if (!fonts.count(assetId))
    {
        Logger::Fatal("[AssetStore] MIssing font with ID: '" + assetId + "'");
    }
    return fonts.at(assetId);
}
