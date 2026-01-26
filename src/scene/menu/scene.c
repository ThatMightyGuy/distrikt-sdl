#include "scene.h"

void menu_init()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Menu Init!");
    engine_set_clear_colorB(20, 20, 20, 255);
}

float x1, x2, yl, y2;
float x = 200, y = 200;

#define POINTS 226

SDL_FPoint points1[POINTS];
SDL_FPoint points2[POINTS];

size_t point;

void menu_update(float deltaTime)
{
    if(input_key(SDL_SCANCODE_ESCAPE))
        engine_exit();
    else if(input_key(SDL_SCANCODE_RETURN))
        scene_set(game_scene);

    SDL_SetRenderScale(Renderer, 4, 4);
    SDL_SetRenderDrawColor(Renderer, SDL_fmodf(scene_time(), 1) * 150 + 105, 0, 0, 255);
    SDL_RenderDebugTextFormat(Renderer, 16, 16, "T: %.3f dT: %.4f", scene_time(), deltaTime);
    SDL_RenderDebugTextFormat(Renderer, 16, 32, "FT: %.2f (%d) fps", engine_get_frametime(), (int)engine_get_framerate());

    float t = scene_time() * 5;

    float ix = input_get("input_hoz");
    float iy = -input_get("input_vert");

    x += ix / 32767.0 * 2.0;
    y += iy / 32767.0 * 2.0;

    const float size = 50;
    x1 = -size * sin(t);
    yl = -size * cos(t);
    x2 = size * sin(t);
    y2 = size * cos(t);

    points1[point] = POINT(x + x1, y + yl);
    points2[point] = POINT(x + 50 + x2, y - 50 + y2);

    point = (point + 1) % POINTS;

    SDL_RenderLine(Renderer, x + x1, y + yl, x + 50 + x2, y - 50 + y2);
    SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColorFloat(Renderer, 0.9, 0.9, 0.9, 1);
    SDL_RenderPoints(Renderer, points1, POINTS);
    SDL_SetRenderDrawColorFloat(Renderer, 0.09, 0.57, 0.32, 1);
    SDL_RenderPoints(Renderer, points2, POINTS);
}

int menu_destroy()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Menu Destroy!");
    return 0;
}
