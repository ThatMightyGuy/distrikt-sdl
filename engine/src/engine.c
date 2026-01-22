#include "engine.h"

SDL_Window *window;
SDL_GLContext glContext;

const uint32_t SDL_INIT_FLAGS = SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC;

void engine_init()
{
    SDL_Init(SDL_INIT_FLAGS);
    window = SDL_CreateWindow("test app", 800, 600, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
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
        input_init();
        SDL_PumpEvents();

        // Calculate deltaTime
        ticksLast = ticksNow;
        ticksNow = SDL_GetPerformanceCounter();
        float deltaTime = (float)(ticksNow - ticksLast) * 1000 / (float)SDL_GetPerformanceFrequency();

        scene_update(deltaTime);

        SDL_GL_SwapWindow(window);
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
    SDL_GL_DestroyContext(glContext);
    SDL_Quit();
}

