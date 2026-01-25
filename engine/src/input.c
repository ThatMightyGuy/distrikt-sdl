#include "input.h"

const bool *keyStates;

int keyCount;

struct
{
    size_t count;
    size_t capacity;
    action_t *data;
} actions;

action_t invalid = {0};

SDL_Gamepad *gamepad;

void input_init()
{
    keyStates = SDL_GetKeyboardState(&keyCount);
    actions.capacity = 16;
    actions.data = calloc(actions.capacity, sizeof(action_t));

    int count;
    SDL_JoystickID *joysticks = SDL_GetGamepads(&count);
    SDL_Gamepad *gamepad = NULL;

    for(int i = 0; i < count; ++i)
    {
        SDL_OpenGamepad(joysticks[0]);
        gamepad = SDL_GetGamepadFromID(joysticks[0]);
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Gamepad: %s", SDL_GetGamepadName(gamepad));
    }
}

SDL_Gamepad *defaultGamepad;

void input_check_sanity()
{
    for(size_t i = 0; i < actions.count; i++)
    {
        if(actions.data[i].gamepad == NULL)
            actions.data[i].gamepad = defaultGamepad;
    }
}

size_t gamepadCount = 0;
void __input_on_gamepad_device(SDL_GamepadDeviceEvent e)
{
    switch(e.type)
    {
        case SDL_EVENT_GAMEPAD_ADDED:
            defaultGamepad = SDL_OpenGamepad(e.which);
            input_check_sanity();
            gamepadCount++;
            break;
        case SDL_EVENT_GAMEPAD_REMOVED:
            SDL_Gamepad *pad = SDL_GetGamepadFromID(e.which);
            SDL_CloseGamepad(pad);
            for(size_t i = 0; i < actions.count; i++)
            {
                if(actions.data[i].gamepad == pad)
                    actions.data[i].gamepad = NULL;
            }
            break;
    }
}

void __input_on_mouse(SDL_MouseMotionEvent e)
{

}

void __input_on_mwheel(SDL_MouseWheelEvent e)
{

}

void __input_on_mouse_down(SDL_MouseButtonEvent e)
{

}

void __input_on_mouse_up(SDL_MouseButtonEvent e)
{

}

void __input_on_key_down(SDL_KeyboardEvent e)
{

}

void __input_on_key_up(SDL_KeyboardEvent e)
{

}

/// TODO: Potential optimization for binary search
///       Probably unnecessary though
bool input_register(action_t action, bool force)
{
    SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Registering input '%s'", action.name);
    if(actions.count >= actions.capacity)
    {
        actions.capacity *= 2;
        actions.data = realloc(actions.data, actions.capacity * sizeof(action_t));
        assert(actions.data != NULL);
    }

    for(size_t i = 0; i < actions.count; ++i)
    {
        if(strcmp(actions.data[i].name, action.name) == 0)
        {
            if(force)
            {
                actions.data[i] = action;
                return true;
            }
            return false;
        }

        if(memcmp(&actions.data[i], &invalid, sizeof(action_t)) == 0)
        {
            actions.data[i] = action;
            return true;
        }
    }
    actions.data[actions.count++] = action;
    return true;
}

bool input_deregister(const char *name)
{
    for(size_t i = 0; i < actions.count; ++i)
    {
        if(strcmp(actions.data[i].name, name) == 0)
        {
           actions.data[i] = invalid;
           return true;
        }
    }
    return false;
}

Sint16 action_poll(action_t action)
{
    int keyboard = input_key(action.keyPos) ? SDL_MAX_SINT16 : 0;
    int axis = 0;
    int button = SDL_GetGamepadButton(action.gamepad, action.buttonPos) ? SDL_MAX_SINT16 : 0;

    if(action.isAxis)
    {
        keyboard -= input_key(action.keyNeg) ? SDL_MAX_SINT16 : 0;

        axis = SDL_GetGamepadAxis(action.gamepad, action.axis);
        if(action.invertAxis)
            axis = -axis;

        button -= SDL_GetGamepadButton(action.gamepad, action.buttonNeg) ? SDL_MAX_SINT16 : 0;
    }

    int value = keyboard + axis + button;

    if(value < SDL_MIN_SINT16)
        return SDL_MIN_SINT16;
    if(value > SDL_MAX_SINT16)
        return SDL_MAX_SINT16;
    return value;
}

/// TODO: Test this
Sint16 input_get(const char *name)
{
    for(size_t i = 0; i < actions.count; ++i)
    {
        if(strcmp(actions.data[i].name, name) == 0)
           return action_poll(actions.data[i]);
    }

    return 0;
}

bool input_key(SDL_Scancode scan)
{
    if(scan <= 0 || scan >= keyCount)
        return false;
    return keyStates[scan];
}

void input_destroy()
{
    actions.count = 0;
    actions.capacity = 0;
    free(actions.data);
    SDL_CloseGamepad(gamepad);
}