#pragma once

#include <math.h>
#include <assert.h>

#include <engine/engine.h>
#include <engine/scene.h>
#include <engine/input.h>

#include "common.h"
#include "scene/game/scene.h"

void menu_init();

void menu_update(float deltaTime);

int menu_destroy();

static const scene_t menu_scene = { menu_init, menu_update, menu_destroy, 1.0 };
