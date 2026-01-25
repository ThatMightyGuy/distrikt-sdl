#include "render.h"

const SDL_WindowFlags SDL_INIT_FLAGS = SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC;

SDL_Window *window;

SDL_Renderer *Renderer;

SDL_Color clearColor = {0};

void render_init(const char *title, int w, int h, SDL_WindowFlags flags)
{
    SDL_Init(SDL_INIT_FLAGS);
    window = SDL_CreateWindow(title, w, h, flags);
    Renderer = SDL_CreateRenderer(window, NULL);
    if(Renderer == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Unable to open a graphics context: %s", SDL_GetError());
    SDL_SetRenderTarget(Renderer, NULL);
    SDL_SetRenderVSync(Renderer, 1);
}

SDL_Window *engine_get_window()
{
    return window;
}

SDL_Renderer *engine_get_renderer()
{
    return Renderer;
}

void engine_render_clear()
{
    SDL_Color oldDrawColor;
    SDL_GetRenderDrawColor(
        Renderer,
        &oldDrawColor.r,
        &oldDrawColor.g,
        &oldDrawColor.b,
        &oldDrawColor.a
    );
    SDL_SetRenderDrawColor(
        Renderer,
        clearColor.r,
        clearColor.g,
        clearColor.b,
        clearColor.a
    );
    SDL_RenderClear(Renderer);
    SDL_SetRenderDrawColor(
        Renderer,
        oldDrawColor.r,
        oldDrawColor.g,
        oldDrawColor.b,
        oldDrawColor.a
    );
}

SDL_Color engine_get_clear_color()
{
    return clearColor;
}

void engine_set_clear_color(SDL_Color color)
{
    clearColor = color;
}

void engine_set_clear_colorB(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    clearColor = (SDL_Color) { r, g, b, a };
}

SDL_Color engine_get_draw_color()
{
    SDL_Color col;
    SDL_GetRenderDrawColor(
        Renderer,
        &col.r,
        &col.g,
        &col.b,
        &col.a
    );
    return col;
}

void engine_set_draw_color(SDL_Color color)
{
    SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
}

void render_destroy()
{
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
