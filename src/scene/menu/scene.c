#include "scene.h"

void menu_init()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Menu Init!");
    engine_set_clear_colorB(20, 20, 20, 255);
}

float x1, x2, yl, y2;

void menu_update(float deltaTime)
{
    if(input_key(SDL_SCANCODE_ESCAPE))
        engine_exit();
    else if(input_key(SDL_SCANCODE_RETURN))
        scene_set(game_scene);

    SDL_SetRenderScale(engine_get_renderer(), 4, 4);
    SDL_SetRenderDrawColor(engine_get_renderer(), (int)(runtime() * 10) % 255, 0, 0, 255);
    SDL_RenderDebugTextFormat(engine_get_renderer(), 16, 16, "dT: %.2f (%d) fps", deltaTime, (int)(1000/deltaTime));

    float t = runtime() * 0.005;

    const float size = 50;
    x1 = -size * sin(t);
    yl = -size * cos(t);
    x2 = size * sin(t);
    y2 = size * cos(t);
    SDL_RenderLine(engine_get_renderer(), 200 + x1, 200 + yl, 250 + x2, 150 + y2);
}

int menu_destroy()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Menu Destroy!");
    return 0;
}
