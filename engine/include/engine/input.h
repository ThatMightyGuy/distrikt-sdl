#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_log.h>

// Gamepad and keyboard input abstraction
// If the action is strictly boolean, only positive inputs will be considered
typedef struct
{
    const char *name;
    SDL_Scancode keyPos;
    SDL_Scancode keyNeg;
    // Is the action an axis or a button?
    bool isAxis;
    SDL_Gamepad *gamepad;
    SDL_GamepadAxis axis;
    bool invertAxis;
    SDL_GamepadButton buttonPos;
    SDL_GamepadButton buttonNeg;
} action_t;

// Initialize the input system
void input_init();

// Run right before handoff
// so that the engine can assign input devices if possible
void input_check_sanity();

void __input_on_gamepad_device(SDL_GamepadDeviceEvent e);

void __input_on_mouse(SDL_MouseMotionEvent e);

void __input_on_mwheel(SDL_MouseWheelEvent e);

void __input_on_mouse_down(SDL_MouseButtonEvent e);

void __input_on_mouse_up(SDL_MouseButtonEvent e);

void __input_on_key_down(SDL_KeyboardEvent e);

void __input_on_key_up(SDL_KeyboardEvent e);

// Register an input action
// Will update an existing action entry if forced
// Returns true if successful
// Returns false if there was a name conflict (unless forced)
bool input_register(action_t action, bool force);

// Deregister an input action
// Returns true if successful
// Returns false if the action was not found
bool input_deregister(const char *name);

// Returns an input value
// Returns 0 or SDL_MAX_SINT16 if the action is set up as boolean
// Returns 0 if the action does not exist
Sint16 input_get(const char *name);

// Debug function, do not use in production
// Checks if a key is currently pressed
// Look into SDL_GetKeyboardState for more details
// You likely want actions or SDL input events instead of this
bool input_key(SDL_Scancode scan);

// Destroy the input system
// Frees the actions list
void input_destroy();
