#pragma once

#include <engine/object.h>
#include <engine/scene.h>
#include <engine/component/debugrender.h>
#include <engine/component/spriterender.h>

typedef struct {
    object_t object;
    spriterender_t sprite;
    debugrender_t debug;
} player_t;

void player_init(player_t *player);

void player_destroy(player_t *player);
