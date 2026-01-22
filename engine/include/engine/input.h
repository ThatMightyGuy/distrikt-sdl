#pragma once

#include <stdbool.h>

#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_gamepad.h>

void input_init();

bool input_key(int scan);
