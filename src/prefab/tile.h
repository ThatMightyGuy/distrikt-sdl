#pragma once

#include <engine/object.h>
#include <engine/scene.h>
#include <engine/component/debugrender.h>
#include <engine/component/spriterender.h>

typedef struct
{
    char name[128];
    SDL_Texture **textureSet;
    size_t textureCount;
    bool isStable;
    bool isUnderground;
    bool isElevated;
    bool isDecoration;
    bool isBuilding;
} tile_t;

void tile_create(tile_t *tile, const char *name, const char *texturePaths[], size_t textureCount);

void tile_destroy(tile_t *tile);