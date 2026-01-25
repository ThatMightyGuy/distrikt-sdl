#pragma once

#include <stddef.h>

#include <SDL3/SDL_rect.h>

#include "util.h"

typedef struct
{
    // SDL_Bitmap spritesheet;
    // index?
    SDL_FPoint position;
    SDL_FPoint scale;
    SDL_FPoint origin;
    float rotation;

    da_t children;
} object_t;

object_t object_init();