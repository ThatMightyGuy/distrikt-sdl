#include "asset.h"

da_t textures;
da_t texturePaths;

SDL_Renderer *rend;

#define __MISSING_TEXTURE_SIZE 2
SDL_Color missingPixels[__MISSING_TEXTURE_SIZE * __MISSING_TEXTURE_SIZE];
SDL_Texture *missingTexture;

void asset_init(SDL_Renderer *renderer)
{
    textures = da_init(sizeof(SDL_Texture*));
    texturePaths = da_init(sizeof(const char*));

    rend = renderer;

    for(int x = 0; x < __MISSING_TEXTURE_SIZE; ++x)
    {
        for(int y = 0; y < __MISSING_TEXTURE_SIZE; ++y)
        {
            bool color = (x < __MISSING_TEXTURE_SIZE / 2) == (y < __MISSING_TEXTURE_SIZE / 2);
            missingPixels[x * __MISSING_TEXTURE_SIZE + y] = color ? (SDL_Color){ 255, 0, 255, 255 } : (SDL_Color){ 0, 0, 0, 255 };
        }
    }

    SDL_Surface *missingSurface = SDL_CreateSurfaceFrom(
        __MISSING_TEXTURE_SIZE,
        __MISSING_TEXTURE_SIZE,
        SDL_PIXELFORMAT_RGBA32,
        &missingPixels,
        __MISSING_TEXTURE_SIZE * 4
    );
    missingTexture = SDL_CreateTextureFromSurface(rend, missingSurface);
    SDL_DestroySurface(missingSurface);
    SDL_SetTextureScaleMode(missingTexture, SDL_SCALEMODE_NEAREST);
}

char *as_local(const char *path)
{
    char *localpath = NULL;
    SDL_asprintf(&localpath, "%s%s", SDL_GetBasePath(), path);
    return localpath;
}

SDL_Texture *get_missing_texture()
{
    return missingTexture;
}

SDL_Surface *surface_load(const char *path)
{
    char *localpath = as_local(path);
    SDL_Surface *surface = IMG_Load(localpath);
    SDL_free(localpath);
    if(surface == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture file not found: '%s'", path);
        return NULL;
    }
    return surface;
}

SDL_Texture *texture_load(const char *path)
{
    char *localPath = as_local(path);
    // Use cached texture if present
    for(size_t i = 0; i < texturePaths.count; ++i)
    {
        if(SDL_strcasecmp(da_at(&texturePaths, i), localPath) == 0)
            return da_at(&textures, i);
    }

    SDL_Texture *tex = IMG_LoadTexture(rend, localPath);
    if(tex == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create static texture: '%s'", SDL_GetError());
        return get_missing_texture();
    }
    da_append(&textures, &tex);
    da_append(&texturePaths, localPath);
    return tex;
}

void asset_destroy()
{
    for(size_t i = 0; i < textures.count; ++i)
    {
        SDL_DestroyTexture(da_at(&textures, i));
    }
    da_free(&textures);
    da_free(&texturePaths);
    SDL_DestroyTexture(missingTexture);
}