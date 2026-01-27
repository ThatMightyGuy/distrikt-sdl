#include "object.h"

object_t object_init()
{
    object_t result = {0};
    result.children = da_init(sizeof(object_t));
    result.components = da_init(sizeof(component_t));
    return result;
}

SDL_FPoint object_position(object_t object)
{
    SDL_FPoint pos = object.position;
    object_t *parent = object.parent;

    while(parent != NULL)
    {
        pos.x += parent->position.x;
        pos.y += parent->position.y;
        parent = parent->parent;
    }

    return pos;
}

void add_component(object_t *object, component_t *component)
{
    da_put(&object->components, component);
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
