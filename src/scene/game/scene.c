#include "scene.h"

void init()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Game Init!");
}

void update(float deltaTime)
{
    if(input_key(SDL_SCANCODE_ESCAPE))
        engine_exit();
}

int destroy()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Game Destroy!");
    return 0;
}
