#include <stdio.h>

#include <engine/engine.h>
#include <engine/scene.h>

#include "scene/game/scene.h"

int main() {
    engine_init();

    // Default scene would be scene/menu
    scene_set(game_scene);

    engine_handoff();

    engine_destroy();

    return 0;
}
