#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL_rect.h>

#define POINT(x, y) (SDL_FPoint) { x, y }

typedef struct
{
    void *data;
    size_t capacity;
    size_t count;
    size_t typesize;
} da_t;

// Create a new dynamic array
da_t da_init(size_t typesize);

// Grab an element by its index
void *da_at(da_t *list, size_t index);

// Grab the last element
void *da_last(da_t *list);

// Append an item to the end
void da_append(da_t *list, void *value);

// Set an element at index to a value
void da_set(da_t *list, size_t index, void *value);

// Put an item in the first NULL spot, or append if NULL wasn't found
void da_put(da_t *list, void *value);

// Clear a dynamic array
void da_clear(da_t *list);

// Destroy an array and free held resources
void da_free(da_t *list);

// Get points that make up a rectangle, wound clockwise with points[0] being the upper left corner
void rect_to_points(SDL_FRect rect, SDL_FPoint points[4]);

// Rotate a point around another point by 'angle' radians
SDL_FPoint point_rotate(SDL_FPoint point, SDL_FPoint origin, float angle);

float degrees(float radians);
