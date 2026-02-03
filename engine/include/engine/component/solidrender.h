#pragma once

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>

#include "../object.h"
#include "../scene.h"
#include "../engine.h"

typedef struct
{
    component_t component;

    SDL_Texture *texture;
    // Texture tint
    SDL_Color color;
    // Draw blend mode used for rendering
    SDL_BlendMode blendMode;
    // Texture mirroring mode
    SDL_FlipMode flip;
} solidrender_t;

solidrender_t solidrender_init();
