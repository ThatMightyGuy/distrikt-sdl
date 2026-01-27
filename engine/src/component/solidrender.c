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
    SDL_RenderTextureAffine(renderer, tex, NULL, &object->origin, &cont->affineTR, &cont->affineBL);
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
        POINT(100, 100),
        POINT(0, 0)
    };
    result.component.container = &result;
    return result;
}
