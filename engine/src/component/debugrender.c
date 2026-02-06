#include "component/debugrender.h"

void __debugrender(object_t *object, void *container)
{
    SDL_Renderer *renderer = engine_get_renderer();
    SDL_Color dc;
    SDL_GetRenderDrawColor(renderer, &dc.r, &dc.g, &dc.b, &dc.a);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_FRect bounds = {
        -object->origin.x,
        object->origin.y,
        object->scale.x,
        object->scale.y
    };
    SDL_FPoint points[5];
    rect_to_points(bounds, points);

    for(size_t i = 0; i < 4; i++)
    {
        points[i] = point_rotate(points[i], object->position, -object->rotation + 3.141592);
        points[i] = world_to_screen(points[i]);
    }
    // Last point should line up with the first one
    points[4] = points[0];
    SDL_RenderLines(renderer, points, 5);

    SDL_FPoint position = world_to_screen(object->position);
    SDL_FPoint orig = point_rotate(object->origin, POINT(0, 0), -object->rotation);
    SDL_SetRenderDrawColor(renderer, 100, 170, 0, 255);

    SDL_FPoint origin = { position.x - orig.x, position.y + orig.y };
    SDL_RenderLine(renderer, position.x, position.y, origin.x, origin.y);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderPoint(renderer, position.x, position.y);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderPoint(renderer, origin.x, origin.y);

    SDL_SetRenderDrawColor(renderer, dc.r, dc.g, dc.b, dc.a);
}

void debugrender_init(debugrender_t *comp)
{
    *comp = (debugrender_t) {
        "debugrender",
        true,
        __debugrender,
        NULL,
    };
}
