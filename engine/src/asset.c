#include "asset.h"

da_t surfaces;
da_t textures;

SDL_Renderer *rend;

SDL_Color missingPixels[16 * 16];
SDL_Surface *missingSurface;
SDL_Texture *missingTexture;

void asset_init(SDL_Renderer *renderer)
{
    surfaces = da_init(sizeof(SDL_Surface*));
    textures = da_init(sizeof(SDL_Texture*));

    rend = renderer;

    for(int x = 0; x < 16; ++x)
    {
        for(int y = 0; y < 16; ++y)
        {
            bool color = (x < 8) == (y < 8);
            missingPixels[x * 16 + y] = color ? (SDL_Color){ 255, 0, 255, 255 } : (SDL_Color){ 0, 0, 0, 255 };
        }
    }

    missingSurface = SDL_CreateSurfaceFrom(16, 16, SDL_PIXELFORMAT_RGBA32, &missingPixels, 0);
    missingTexture = SDL_CreateTextureFromSurface(rend, missingSurface);
}

SDL_Texture *get_missing_texture()
{
    return missingTexture;
}

SDL_Surface *surface_load(const char *path)
{
    SDL_Surface *surf = IMG_Load(path);
    if(surf == NULL)
    {
        // SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture not found: '%s'", path);
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load texture: '%s'", SDL_GetError());
        return NULL;
    }
    da_append(&surfaces, &surf);
    return surf;
}

SDL_Texture *texture_load(const char *path)
{
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surface_load(path));
    if(tex == NULL)
    {
        return NULL;
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

    for(size_t i = 0; i < surfaces.count; ++i)
        SDL_DestroySurface(surfaces.data[i]);
    da_free(&surfaces);
    SDL_DestroySurface(missingSurface);
}