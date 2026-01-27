#pragma once

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>

#include "../object.h"
#include "../scene.h"
#include "../engine.h"

typedef struct
{
    component_t component;
} debugrender_t;

debugrender_t debugrender_init();
