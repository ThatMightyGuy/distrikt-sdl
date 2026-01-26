#pragma once

#include <stddef.h>

#include <SDL3/SDL_rect.h>

#include "util.h"

#define POINT(x, y) (SDL_FPoint) { x, y }


typedef struct
{
    // SDL_Bitmap spritesheet;
    // index?
    SDL_FPoint position;
    SDL_FPoint scale;
    SDL_FPoint origin;
    float rotation;

    object_t *parent;
    da_t children;
} object_t;

object_t object_init();

SDL_FPoint object_position(object_t object);

void object_destroy(object_t *object);