#pragma once

#include <stddef.h>
#include <stdbool.h>

#include <SDL3/SDL.h>

#include "input.h"
#include "scene.h"

static SDL_Window *Window;

static SDL_Renderer *Renderer;

// static SDL_Color ClearColor = {0};

// Initialize engine and SDL state
void engine_init();

// Hand off flow control to the engine
void engine_handoff();

// Force break out of the engine loop
// Keeps the game window alive, but frozen
void engine_exit();

// Destroy engine and SDL state
void engine_destroy();

SDL_Window *engine_get_window();

SDL_Renderer *engine_get_renderer();

SDL_Color engine_get_clear_color();

void engine_set_clear_color(SDL_Color color);

void engine_set_clear_colorB(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

