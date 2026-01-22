#pragma once

#include <engine/engine.h>
#include <engine/scene.h>
#include <engine/input.h>

void game_init();

void game_update(float deltaTime);

int game_destroy();

static scene_t game_scene = { game_init, game_update, game_destroy };