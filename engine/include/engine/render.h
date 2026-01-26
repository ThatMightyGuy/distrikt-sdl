#pragma once

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include "object.h"
#include "scene.h"

void render_init(const char *title, int w, int h, SDL_WindowFlags flags);

// Get the main SDL window
SDL_Window *engine_get_window();

// Get the main SDL window renderer
SDL_Renderer *engine_get_renderer();

object_t *engine_get_camera();

// Clear the buffer with a color
// set by engine_set_clear_color
void engine_render_clear();

// Get the color used for buffer clearing
SDL_Color engine_get_clear_color();

// Set the color used for buffer clearing
void engine_set_clear_color(SDL_Color color);

// Set the color used for buffer clearing
void engine_set_clear_colorB(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

SDL_Color engine_get_draw_color();

void engine_set_draw_color(SDL_Color color);

SDL_FPoint world_to_screen(SDL_FPoint point);

void render_destroy();
