#include "tile.h"

void tile_create(tile_t *tile, const char *name, const char *texturePaths[], size_t textureCount)
{
    strcpy_s(tile->name, sizeof(tile->name), name);
    tile->textureSet = calloc(textureCount, sizeof(SDL_Texture*));
    for(size_t i = 0; i < textureCount; ++i)
        tile->textureSet[i] = texture_load(texturePaths[i]);

    tile->isStable = true;
    tile->isUnderground = false;
    tile->isElevated = false;
    tile->isDecoration = false;
    tile->isBuilding = false;
}

void tile_destroy(tile_t *tile)
{
    free(tile->textureSet);
    tile->textureCount = 0;
}