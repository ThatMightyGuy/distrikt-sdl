#include <stdio.h>

#include <engine/engine.h>
#include <engine/input.h>
#include <engine/scene.h>

#include "common.h"
#include "scene/menu/scene.h"

void register_inputs()
{
    // int count;
    // SDL_JoystickID *joysticks = SDL_GetGamepads(&count);
    // SDL_Gamepad *gamepad = NULL;
    // if(count > 0)
    // {
    //     SDL_OpenGamepad(joysticks[0]);
    //     gamepad = SDL_GetGamepadFromID(joysticks[0]);
    //     SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Gamepad: %s", SDL_GetGamepadName(gamepad));
    // }

    action_t action = {
        "input_vert",
        SDL_SCANCODE_UP,
        SDL_SCANCODE_DOWN,
        true,
        NULL,
        SDL_GAMEPAD_AXIS_RIGHTY,
        true,
        SDL_GAMEPAD_BUTTON_DPAD_UP,
        SDL_GAMEPAD_BUTTON_DPAD_DOWN
    };
    input_register(action, false);

    action = (action_t) {
        "input_hoz",
        SDL_SCANCODE_RIGHT,
        SDL_SCANCODE_LEFT,
        true,
        NULL,
        SDL_GAMEPAD_AXIS_RIGHTX,
        false,
        SDL_GAMEPAD_BUTTON_DPAD_RIGHT,
        SDL_GAMEPAD_BUTTON_DPAD_LEFT
    };
    input_register(action, false);
}

int main() {
    engine_init("test app", 800, 600, SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN);

    register_inputs();

    // common_init();
    // Default scene would be scene/menu
    scene_set(menu_scene);

    input_check_sanity();
    
    engine_handoff();

    engine_destroy();

    return 0;
}
