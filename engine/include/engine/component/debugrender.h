#pragma once

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>

#include "../object.h"
#include "../scene.h"
#include "../engine.h"

typedef struct
{
    COMPONENT_PREAMBLE
} debugrender_t;

void debugrender_init(debugrender_t *comp);
