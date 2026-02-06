#include "util.h"

da_t da_init(size_t typesize)
{
    return (da_t) {
        calloc(32, typesize),
        32,
        0,
        typesize
    };
}

void *da_at(da_t *list, size_t index)
{
    if(index >= list->count)
        return NULL;
    return (char*)list->data + (list->typesize * index);
}

void expand(da_t *list)
{
    if(list->count >= list->capacity)
    {
        list->data = realloc(list->data, list->capacity * 2 * list->typesize);
        void *dest = (char*)list->data + (list->typesize * list->capacity);
        memset(dest, 0, list->capacity * list->typesize);
        list->capacity *= 2;
    }
}

void da_append(da_t *list, void *value)
{
    expand(list);
    void *dest = (char*)list->data + (list->typesize * list->count);
    memcpy(dest, value, list->typesize);
    list->count++;
}

void da_set(da_t *list, size_t index, void *value)
{
    if(index >= list->count)
        return;
    memcpy(da_at(list, index), value, list->typesize);
}

void da_put(da_t *list, void *value)
{
    for(size_t i = 0; i < list->count; ++i)
    {
        if(da_at(list, i) == NULL)
        {
            da_set(list, i, value);
            return;
        }
    }
    da_append(list, value);
}

void da_clear(da_t *list)
{
    list->count = 0;
}

void da_free(da_t *list)
{
    list->capacity = 0;
    list->count = 0;
    list->typesize = 0;
    free(list->data);
}

void rect_to_points(SDL_FRect rect, SDL_FPoint points[4])
{
    points[0] = POINT(rect.x, rect.y);
    points[1] = POINT(rect.x + rect.w, rect.y);
    points[2] = POINT(rect.x + rect.w, rect.y + rect.h);
    points[3] = POINT(rect.x, rect.y + rect.h);
}

SDL_FPoint point_rotate(SDL_FPoint point, SDL_FPoint origin, float angle)
{
    SDL_FPoint result = { point.x - origin.x, point.y - origin.y };

    float sine = sin(angle);
    float cosine = cos(angle);

    result.x = (point.x * cosine - point.y * sine) + origin.x;
    result.y = (point.y * cosine + point.x * sine) + origin.y;

    return result;
}

float degrees(float radians)
{
    const float rad2deg = 57.29578;
    return radians * rad2deg;
}
