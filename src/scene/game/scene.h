#pragma once

#include <engine/engine.h>
#include <engine/scene.h>
#include <engine/input.h>

void init();

void update(float deltaTime);

int destroy();

static scene_t game_scene = { init, update, destroy };