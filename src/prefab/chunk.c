#include "chunk.h"

float noisegen(int x, int y, chunkgen_state *state)
{
    float scale = state->scale;
    float height = 0;
    for(size_t layer = 0; layer < state->layers; ++layer)
    {
        /// TODO: Implement the terrain generator
        // height += 

        scale *= state->dropoff;
    }
}

void chunk_generate(chunk_t *chunk, chunkgen_state *state)
{
    for(size_t x = 0; x < CHUNK_SIDE; ++x)
    {
        int ax = chunk->x * CHUNK_SIDE + x;
        for(size_t y = 0; y < CHUNK_SIDE; ++y)
        {
            int ay = chunk->y * CHUNK_SIDE + y;
            chunk->ground[chunk->x * CHUNK_SIDE + chunk->y] = noisegen(ax, ay, state);
        }
    }
}
