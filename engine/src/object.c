#include "object.h"

object_t object_init()
{
    object_t result = {0};
    result.children = da_init(sizeof(object_t));
    return result;
}

void object_destroy(object_t *object)
{
    for(size_t i = 0; i < object->children.count; i++)
        object_destroy((object_t*)object->children.data[i]);

    da_free(&object->children);
    object->position = (SDL_FPoint){0};
    object->scale = (SDL_FPoint){0};
    object->origin = (SDL_FPoint){0};
    object->rotation = 0;
}
