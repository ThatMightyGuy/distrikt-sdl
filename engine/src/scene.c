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

void scene_update(float deltaTime)
{
    if(__scene.update != NULL)
        __scene.update(deltaTime);
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