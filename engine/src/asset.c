#include "asset.h"

da_t textures;

SDL_Renderer *rend;

#define __MISSING_TEXTURE_SIZE 2
SDL_Color missingPixels[__MISSING_TEXTURE_SIZE * __MISSING_TEXTURE_SIZE];
SDL_Texture *missingTexture;

void asset_init(SDL_Renderer *renderer)
{
    textures = da_init(sizeof(SDL_Texture*));

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
    // SDL_Surface *surface = surface_load(path);
    // if(surface == NULL)
    //     return get_missing_texture();
    SDL_Texture *tex = IMG_LoadTexture(rend, as_local(path));
    // SDL_DestroySurface(surface);
    if(tex == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create static texture: '%s'", SDL_GetError());
        return get_missing_texture();
    }
    da_append(&textures, &tex);
    return tex;
}

void asset_destroy()
{
    for(size_t i = 0; i < textures.count; ++i)
        SDL_DestroyTexture(textures.data[i]);
    da_free(&textures);
    SDL_DestroyTexture(missingTexture);
}