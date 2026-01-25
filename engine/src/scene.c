#include "scene.h"

int scene_set(scene_t scene)
{
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Scene change!");
    int err = scene_destroy();

    if(!err)
    {
        __scene = scene;
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Calling new scene's initiator...");
        scene_init();
    }
    else
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Got an error during scene destruction (%d)", err);
    }
    return err;
}

void scene_init()
{
    if(__scene.init != NULL)
        __scene.init();
    else
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init is null");
}

float runTime = 0;

void scene_update(float deltaTime)
{
    deltaTime *= __scene.timescale;
    if(__scene.update != NULL)
        __scene.update(deltaTime);
    runTime += deltaTime;
}

int scene_destroy()
{
    int status = 0;
    if(__scene.destroy != NULL)
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Calling scene destructor...");
        status = __scene.destroy();
    }

    __scene = (scene_t){ NULL, NULL, NULL };

    return status;
}

float scene_time()
{
    return runTime;
}

/// TODO: Fix rotation bounding box
void scene_drawdebug(object_t object)
{
    SDL_Renderer *renderer = engine_get_renderer();
    SDL_Color dc;
    SDL_GetRenderDrawColor(renderer, &dc.r, &dc.g, &dc.b, &dc.a);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_FRect bounds = {
        object.position.x - object.origin.x,
        object.position.y + object.origin.y,
        object.scale.x,
        object.scale.y
    };
    SDL_RenderRect(renderer, &bounds);

    SDL_SetRenderDrawColor(renderer, 100, 170, 0, 255);
    SDL_FPoint origin = { object.position.x - object.origin.x, object.position.y + object.origin.y };
    SDL_RenderLine(renderer, object.position.x, object.position.y, origin.x, origin.y);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderPoints(renderer, &object.position, 1);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderPoints(renderer, &origin, 1);

    SDL_SetRenderDrawColor(renderer, dc.r, dc.g, dc.b, dc.a);
}
