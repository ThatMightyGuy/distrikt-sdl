#include "input.h"

const bool *keyStates;

int keyCount;

void input_init()
{
    keyStates = SDL_GetKeyboardState(&keyCount);
}

bool input_key(int scan)
{
    if(scan < 0 || scan >= keyCount)
        return false;
    return keyStates[scan];
}
