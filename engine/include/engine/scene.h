#pragma once

#include <stddef.h>

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_timer.h>

#include "engine.h"
#include "object.h"
#include "render.h"

typedef struct
{
    // A function to be called when a scene is initialized
    void (*init)(void);

    // A function to be called every frame
    void (*update)(float);

    // A function to be called when the scene is changed or the game is closed
    // Returns 0 if successful
    int (*destroy)(void);

    float timescale;
} scene_t;

static scene_t __scene;

// Gracefully set or change current scene
// Calls init() if possible
// Returns 0 if successful
int scene_set(scene_t scene);

// Null-safe scene init function
void scene_init();

// Null-safe scene update function
void scene_update(float deltaTime);

// Null-safe scene destroy function
// Returns 0 if successful or there is no destroy callback
int scene_destroy();

// Get current run time in seconds
float scene_time();

// Draw object pivot and bounding box
void scene_drawdebug(object_t object);

// Add an object to scene hierarchy
// YOU MUST HOLD ONTO THE OBJECT
void scene_add(object_t *object);

