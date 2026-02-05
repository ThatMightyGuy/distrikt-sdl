#include "component/solidrender.h"

void __solidrender(object_t *object, void *container)
{
    solidrender_t *cont = container;
    if(cont == NULL) return;
    SDL_Texture *tex = cont->texture;
    if(tex == NULL) tex = get_missing_texture();

    SDL_Renderer *renderer = engine_get_renderer();

    engine_set_draw_color(cont->color);
    SDL_SetTextureColorMod(
        cont->texture,
        cont->color.r,
        cont->color.g,
        cont->color.b
    );
    SDL_SetTextureAlphaMod(cont->texture, cont->color.a);
    SDL_SetTextureBlendMode(cont->texture, cont->blendMode);

    SDL_FPoint origin = { object->origin.x, -object->origin.y };
    SDL_FPoint start = { object->position.x - origin.x, object->position.y + origin.y };
    start = world_to_screen(start);
    SDL_FRect dest = {
        start.x,
        start.y,
        object->scale.x,
        object->scale.y
    };
    SDL_RenderTextureRotated(renderer, texture_load("assets/test.png"), NULL, &dest, degrees(object->rotation), &origin, cont->flip);
}

solidrender_t solidrender_init()
{
    component_t component = {
        "solidrender",
        true,
        __solidrender,
        NULL,
        NULL
    };
    solidrender_t result = {
        component,
        get_missing_texture(),
        (SDL_Color) { 255, 255, 255, 255 },
        SDL_BLENDMODE_NONE,
        SDL_FLIP_NONE
    };
    result.component.container = &result;
    return result;
}
