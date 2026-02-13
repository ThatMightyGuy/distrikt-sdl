#pragma once

#include <engine/object.h>
#include <engine/scene.h>
#include <engine/component/debugrender.h>
#include <engine/component/spriterender.h>

#define CHUNK_SIDE 32
#define CHUNK_AREA CHUNK_SIDE * CHUNK_SIDE

typedef struct
{
    int x, y;
    object_t underground[CHUNK_AREA];
    object_t ground[CHUNK_AREA];
    object_t decoration[CHUNK_AREA];
    object_t buildings[CHUNK_AREA];
    object_t elevated[CHUNK_AREA];
} chunk_t;

typedef struct
{
    uint64_t seed;
    float scale;
    float dropoff;
    size_t layers;
    uint64_t current;
} chunkgen_state;

typedef struct
{
    float heights[5];
} world_settings;

float noisegen(int x, int y, chunkgen_state *state);

void chunk_generate(chunk_t *chunk, chunkgen_state *state);
