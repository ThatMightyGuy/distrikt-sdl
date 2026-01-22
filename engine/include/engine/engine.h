#pragma once

#include <stddef.h>
#include <stdbool.h>

#include <SDL3/SDL.h>

#include "input.h"
#include "scene.h"

// Initialize engine and SDL state
void engine_init();

// Hand off flow control to the engine
void engine_handoff();

// Force break out of the engine loop
// Keeps the game window alive, but frozen
void engine_exit();

// Destroy engine and SDL state
void engine_destroy();
