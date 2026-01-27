#pragma once

#include <engine/engine.h>
#include <engine/object.h>
#include <engine/scene.h>
#include <engine/input.h>
#include <engine/component/debugrender.h>
#include <engine/component/solidrender.h>

#include "common.h"

void game_init();

void game_update(float deltaTime);

int game_destroy();

static const scene_t game_scene = { game_init, game_update, game_destroy, 1.0 };
