#include "scene.h"

void game_init()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Game Init!");
    engine_set_clear_colorB(255, 0, 0, 255);
}

void game_update(float deltaTime)
{
    if(input_key(SDL_SCANCODE_ESCAPE))
        engine_exit();
}

int game_destroy()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Game Destroy!");
    return 0;
}
