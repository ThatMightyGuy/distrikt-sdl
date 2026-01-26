#include "render.h"

const SDL_WindowFlags SDL_INIT_FLAGS = SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC;

SDL_Window *Window;

SDL_Renderer *Renderer;

object_t *Camera;

object_t camera;

SDL_Color clearColor = {0};

void render_init(const char *title, int w, int h, SDL_WindowFlags flags)
{
    SDL_Init(SDL_INIT_FLAGS);
    Window = SDL_CreateWindow(title, w, h, flags);
    Renderer = SDL_CreateRenderer(Window, NULL);
    if(Renderer == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Unable to open a graphics context: %s", SDL_GetError());
    SDL_SetRenderTarget(Renderer, NULL);
    SDL_SetRenderVSync(Renderer, 1);

    camera = object_init();
    Camera = &camera;
}

SDL_Window *engine_get_window()
{
    return Window;
}

SDL_Renderer *engine_get_renderer()
{
    return Renderer;
}

object_t *engine_get_camera()
{
    return Camera;
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

SDL_FPoint world_to_screen(SDL_FPoint point)
{
    int rw, rh;
    SDL_GetCurrentRenderOutputSize(Renderer, &rw, &rh);
    float sw, sh;
    SDL_GetRenderScale(Renderer, &sw, &sh);
    float w = rw / sw;
    float h = rh / sh;

    SDL_FPoint result;
    result.x = point.x - camera.position.x + w / 2;
    result.y = point.y - camera.position.y;
    result.y = h / 2 - result.y;
    return result;
}

void render_destroy()
{
    object_destroy(Camera);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}
