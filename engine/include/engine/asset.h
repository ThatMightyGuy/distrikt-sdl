#pragma once


#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>

#include "util.h"

void asset_init(SDL_Renderer *renderer);

SDL_Texture *get_missing_texture();

SDL_Surface *surface_load(const char *path);

SDL_Texture *texture_load(const char *path);

void asset_destroy();
