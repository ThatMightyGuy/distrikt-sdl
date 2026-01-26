#pragma once

#include <engine/object.h>
#include <engine/render.h>

extern SDL_Renderer *Renderer;

extern SDL_Window *Window;

extern object_t *Camera;

void common_init();
