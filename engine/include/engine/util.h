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

// Create a new dynamic array
da_t da_init(size_t typesize);

// Append an item to the end
void da_append(da_t *list, void *value);

// Put an item in the first NULL spot, or append if NULL wasn't found
void da_put(da_t *list, void *value);

// Clear a dynamic array
void da_clear(da_t *list);

// Destroy an array and free held resources
void da_free(da_t *list);
