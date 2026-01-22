#include "scene.h"

void menu_init()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Menu Init!");
}

void menu_update(float deltaTime)
{
    if(input_key(SDL_SCANCODE_ESCAPE))
        engine_exit();
    else if(input_key(SDL_SCANCODE_KP_ENTER))
        scene_set(game_scene);
}

int menu_destroy()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Menu Destroy!");
    return 0;
}
