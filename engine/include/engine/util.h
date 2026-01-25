#pragma once

#include <stddef.h>
#include <stdlib.h>

typedef struct
{
    void **data;
    size_t capacity;
    size_t count;
    size_t typesize;
} da_t;

da_t da_init(size_t typesize);

void da_append(da_t *list, void *value);

void da_clear(da_t *list);

void da_free(da_t *list);
