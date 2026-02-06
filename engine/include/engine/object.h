#pragma once

#include <stddef.h>

#include <SDL3/SDL_rect.h>

#include "util.h"

typedef struct object_t
{
    // SDL_Bitmap spritesheet;
    // index?
    SDL_FPoint position;
    SDL_FPoint scale;
    SDL_FPoint origin;
    float rotation;

    da_t components;
    struct object_t *parent;
    da_t children;
} object_t;

#define COMPONENT_PREAMBLE \
    const char *name; \
    bool enabled; \
    void (*update)(object_t*, void*); \
    void (*destroy)(object_t*, void*);

typedef struct
{
    COMPONENT_PREAMBLE
} component_t;

object_t object_init();

SDL_FPoint object_position(object_t object);

void add_component(object_t *object, void *component);

void object_destroy(object_t *object);