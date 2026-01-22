#include "engine.h"

const uint32_t SDL_INIT_FLAGS = SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC;

SDL_Color ClearColor = {0};

void render_clear(SDL_Renderer *renderer)
{
    SDL_Color oldDrawColor;
    SDL_GetRenderDrawColor(
        renderer,
        &oldDrawColor.r,
        &oldDrawColor.g,
        &oldDrawColor.b,
        &oldDrawColor.a
    );
    SDL_SetRenderDrawColor(
        renderer,
        ClearColor.r,
        ClearColor.g,
        ClearColor.b,
        ClearColor.a
    );
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(
        renderer,
        oldDrawColor.r,
        oldDrawColor.g,
        oldDrawColor.b,
        oldDrawColor.a
    );
}

void engine_init()
{
    SDL_Init(SDL_INIT_FLAGS);
    Window = SDL_CreateWindow("test app", 800, 600, SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN);
    Renderer = SDL_CreateRenderer(Window, "direct3d");
    if(Renderer == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Unable to open a graphics context: %s", SDL_GetError());
    SDL_SetRenderTarget(Renderer, NULL);
    SDL_SetRenderVSync(Renderer, 1);
    input_init();
}

bool shouldExit;

void engine_handoff()
{
    shouldExit = false;

    Uint64 ticksNow = SDL_GetPerformanceCounter();
    Uint64 ticksLast = 0;

    while (!shouldExit)
    {
        SDL_PumpEvents();

        ticksLast = ticksNow;
        ticksNow = SDL_GetPerformanceCounter();
        float deltaTime = (float)(ticksNow - ticksLast) * 1000 / (float)SDL_GetPerformanceFrequency();

        render_clear(Renderer);
        scene_update(deltaTime);
        SDL_RenderPresent(Renderer);
    }
}

void engine_exit()
{
    shouldExit = true;
    scene_destroy();
}

void engine_destroy()
{
    engine_exit();
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

SDL_Window *engine_get_window()
{
    return Window;
}

SDL_Renderer *engine_get_renderer()
{
    return Renderer;
}

SDL_Color engine_get_clear_color()
{
    return ClearColor;
}

void engine_set_clear_color(SDL_Color color)
{
    ClearColor = color;
}

void engine_set_clear_colorB(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    ClearColor = (SDL_Color){ r, g, b, a };
}
