#pragma once

#include <stddef.h>
#include <stdbool.h>

#include <SDL3/SDL_events.h>

#include "asset.h"
#include "render.h"
#include "input.h"
#include "scene.h"

// Initialize engine and SDL state
void engine_init(const char *title, int w, int h, SDL_WindowFlags flags);

// Is the engine not destroyed?
bool engine_is_alive();

// Reset timers used for deltaTime calculation
// Done after scene load as long loads will cause the game to bork
void engine_reset_frametime();

// Hand off flow control to the engine
void engine_handoff();

float engine_get_frametime();

float engine_get_framerate();

// Force break out of the engine loop
// Keeps the game window alive, but frozen
void engine_exit();

// Destroy engine and SDL state
void engine_destroy();
