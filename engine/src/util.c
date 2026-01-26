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

void expand(da_t *list)
{
    if(list->count >= list->capacity)
        list->data = realloc(list->data, list->capacity * 2 * list->typesize);
}

void da_append(da_t *list, void *value)
{
    expand(list);
    list->data[list->count++] = value;
}

void da_put(da_t *list, void *value)
{
    for(size_t i = 0; i < list->count; ++i)
    {
        if(list->data[i] == NULL)
        {
            list->data[i] = value;
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