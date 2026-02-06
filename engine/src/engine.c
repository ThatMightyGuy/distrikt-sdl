#include "engine.h"

bool is_alive = false;

void engine_init(const char *title, int w, int h, SDL_WindowFlags flags)
{
    is_alive = true;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Renderer init");
    render_init(title, w, h, flags);
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Asset manager init");
    asset_init(engine_get_renderer());
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Input manager init");
    input_init();
}

bool engine_is_alive()
{
    return is_alive;
}

float deltaTime;

bool shouldExit;

void event_poll()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_EVENT_GAMEPAD_ADDED:
            case SDL_EVENT_GAMEPAD_REMOVED:
                __input_on_gamepad_device(event.gdevice);
                break;


            case SDL_EVENT_MOUSE_MOTION:
                __input_on_mouse(event.motion);
                break;


            case SDL_EVENT_MOUSE_WHEEL:
                __input_on_mwheel(event.wheel);
                break;


            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                __input_on_mouse_down(event.button);
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                __input_on_mouse_up(event.button);
                break;


            case SDL_EVENT_KEY_DOWN:
                __input_on_key_down(event.key);
                break;
            case SDL_EVENT_KEY_UP:
                __input_on_key_up(event.key);
                break;


            case SDL_EVENT_QUIT:
                engine_exit();
                return;
        }
    }
}

Uint64 ticksNow, ticksLast;

void engine_reset_frametime()
{
    ticksNow = SDL_GetPerformanceCounter();
    ticksLast = 0;
}

void engine_handoff()
{
    if (!is_alive) return;
    shouldExit = false;

    engine_reset_frametime();

    while (!shouldExit)
    {
        event_poll();

        ticksLast = ticksNow;
        ticksNow = SDL_GetPerformanceCounter();
        deltaTime = (float)(ticksNow - ticksLast) * 1000 / (float)SDL_GetPerformanceFrequency();

        engine_render_clear();
        scene_update(deltaTime / 1000);
        SDL_RenderPresent(engine_get_renderer());
    }
}

float engine_get_frametime()
{
    return deltaTime;
}

float engine_get_framerate()
{
    return 1000 / deltaTime;
}

void engine_exit()
{
    shouldExit = true;
    scene_destroy();
}

void engine_destroy()
{
    is_alive = false;
    engine_exit();
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Destroying the input manager");
    input_destroy();
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Destroying the asset manager");
    asset_destroy();
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Destroying the renderer");
    render_destroy();
}

